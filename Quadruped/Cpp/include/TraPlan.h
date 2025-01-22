#pragma once

#include <Eigen/Dense>
#include "mpcCal.h"
#include <iostream>

using namespace Eigen;

namespace Quadruped {

	class PlanBase {
	protected:
		/* ����Ĺ켣�滮 */
		Vector3d Pbt,Pbc,Vbt,Vbc;
		/* ��˵Ĺ켣�滮 */
		Eigen::Matrix<double, 3, 4> Plt, Plc, Vlt, Vlc;
		/* �滮��� */
		Vector3d Pbr, Vbr;
		Eigen::Matrix<double, 3, 4> Plr, Vlr;
	public:
		void updateBodyHighLevelTar(const Vector3d& _Pbt, const Vector3d& _Vbt)
		{
			this->Pbt = _Pbt;
			this->Vbt = _Vbt;
		}
		void updateFootHighLevelTar(const Eigen::Matrix<double, 3, 4>& _Plt, const Eigen::Matrix<double, 3, 4>& _Vlt)
		{
			this->Plt = _Plt;
			this->Vlt = _Vlt;
		}
		void updateBodyState(const Vector3d& _Pbc, const Vector3d& _Vbc)
		{
			this->Pbc = _Pbc;
			this->Vbc = _Vbc;
		}
		void updateFootState(const Eigen::Matrix<double, 3, 4>& _Plc, const Eigen::Matrix<double, 3, 4>& _Vlc)
		{
			this->Plc = _Plc;
			this->Vlc = _Vlc;
		}
		virtual void useBodyPlan() = 0;
		virtual void useFootPlan() = 0;
		const Vector3d& getBodyPlanPosition()
		{
			return this->Pbr;
		}
		const Vector3d& getBodyPlanVelocity()
		{
			return this->Vbr;
		}
		const Eigen::Matrix<double, 3, 4>& getFootPlanPosition()
		{
			return this->Plr;
		}
		const Eigen::Matrix<double, 3, 4>& getFootPlanVelocity()
		{
			return this->Vlr;
		}
		void setInitBodyPlanPosition(const Eigen::Vector3d& _Pbr)
		{
			this->Pbr = _Pbr;
		}
		void setInitBodyPlanVelocity(const Eigen::Vector3d& _Vbr)
		{
			this->Vbr = _Vbr;
		}
	};

	class BalanceBodyPlanning :public PlanBase
	{
	private:
		/* ��������� */
		Vector4d tumblingAxis;
		/* ��������� */
		Eigen::Matrix<double, 3, 4> tumblingPoint;
		/* ƽ��׶Լ��ϵ����ͨ���Զ����ȶ�ԣ���Լ�֧�Ŷ�����ҵ����ص�ƽ��׷Լ�� */
		double balanceMargin, balanceCone;
		/* �켣�滮mpc������ */
		mpcCal<6, 3, 4, 1, 10> traGenerator;
		/* Ԥ��ʱ�䲽�� */
		double step_t = 0;
		/* mpc����۲� */
		Eigen::Vector3d acc;

		/* ��ȡ�������Լ������� */
		void getTumbling()
		{
			for (int i = 0; i < 4; i++)
			{
				if (i == 3)
				{
					double temp = -(this->Plc.col(0) - this->Plc.col(i)).transpose() * (this->Plc.col(i) - this->Pbc);
					tumblingAxis(i) = temp / (this->Plc.col(0) - this->Plc.col(i)).squaredNorm();
					tumblingPoint.col(i) = this->Plc.col(i) + tumblingAxis(i) * (this->Plc.col(0) - this->Plc.col(i));
				}
				else
				{
					double temp = -(this->Plc.col(i + 1) - this->Plc.col(i)).transpose() * (this->Plc.col(i) - this->Pbc);
					tumblingAxis(i) = temp / (this->Plc.col(i + 1) - this->Plc.col(i)).squaredNorm();
					tumblingPoint.col(i) = this->Plc.col(i) + tumblingAxis(i) * (this->Plc.col(i + 1) - this->Plc.col(i));
				}
			}
			/*std::cout << "Axis: " << std::endl;
			std::cout << tumblingAxis << std::endl;
			std::cout << "Point: " << std::endl;
			std::cout << tumblingPoint << std::endl;*/
		}

		/* �ҵ�ƽ��׶Լ������ */
		void findBalanceCone()
		{
			Eigen::Vector3d g(0, 0, -9.81);
			// �ҵ����ϸ��Լ����(������С�н�)
			double temp = g.dot(this->tumblingPoint.col(0) - this->Pbc) / (g.norm() + (this->tumblingPoint.col(0) - this->Pbc).norm());
			int min_idx = 0;
			for (int i = 0; i < 4; i++)
			{
				double temp1 = g.dot(this->tumblingPoint.col(i) - this->Pbc) / (g.norm() + (this->tumblingPoint.col(i) - this->Pbc).norm());
				if (temp1 < temp)
				{
					min_idx = i;
					temp = temp1;
				}
			}
			balanceCone = balanceMargin * (this->tumblingPoint.col(min_idx) - this->Pbc).block(0, 0, 2, 1).norm() / abs((this->tumblingPoint.col(min_idx) - this->Pbc)(2));
			//std::cout << balanceCone << std::endl;
		}

		/* ���²���ʽԼ�� */
		void updateIeqConstrain()
		{
			// ƽ��Լ��ת��Ϊ����׶Լ��
			Eigen::Matrix<double, 4, 3> cA;
			cA.setZero();
			cA << 1, 0, this->balanceCone, -1, 0, this->balanceCone, 0, 1, this->balanceCone, 0, -1, this->balanceCone;
			Eigen::Vector4d Aub, Alb;
			Aub.setConstant(-(this->balanceCone * -9.81));
			Alb.setConstant(-100000.);
			this->traGenerator.setBoxConstrain(cA, Alb, Aub);
			/*std::cout << "cA: " << std::endl;
			std::cout << cA << std::endl;
			std::cout << "Alb: " << std::endl;
			std::cout << Alb << std::endl;
			std::cout << "Aub: " << std::endl;
			std::cout << Aub << std::endl;*/
		}

		/* ����Ż����Ⲣ�õ�����켣 */
		void getSolution()
		{
			Eigen::Vector<double, 6> y, x;
			Eigen::Vector3d Py(this->Pbr(0), this->Pbr(1), this->Pbt(2));
			x.block(0, 0, 3, 1) = this->Pbr;
			x.block(3, 0, 3, 1) = this->Vbr;
			y.block(0, 0, 3, 1) = Py;
			y.block(3, 0, 3, 1) = this->Vbt;
			/*std::cout << "x: " << std::endl;
			std::cout << x << std::endl;
			std::cout << "y: " << std::endl;
			std::cout << y << std::endl;*/
			this->traGenerator.mpc_update(y, x, 100, 1.);
			this->traGenerator.mpc_solve();
			this->acc = this->traGenerator.getOutput();
			this->Vbr = this->Vbr + 0.002 * this->traGenerator.getOutput();
			this->Pbr = this->Pbr + 0.002 * this->Vbr;
		}

	public:
		/* ���캯�� */
		BalanceBodyPlanning():traGenerator(PL_LOW) {
			// ��ʼ������
			this->balanceCone = 0.5;
			this->balanceMargin = 0.5;
			this->Pbr.setZero();
			this->Vbr.setZero();
		}
		/* ʹ�û���滮�� */
		void useBodyPlan() override
		{
			this->getTumbling();
			this->findBalanceCone();
			this->updateIeqConstrain();
			this->getSolution();
		}
		/* ʹ����˹滮�� */
		void useFootPlan() override
		{

		}
		/* ���¹滮������ */
		void updateParams(const double& _t, const double& _balanceMargin, const Eigen::Matrix<double, 6, 6>& _Q, const Eigen::Matrix<double, 6, 6>& _F, const Eigen::Matrix<double, 3, 3>& _R, const Eigen::Matrix<double,3,3>& _W)
		{
			this->step_t = _t;
			this->balanceMargin = _balanceMargin;
			// ��ʼ���켣������
			MatrixXd A, B;
			A.resize(6, 6);
			B.resize(6, 3);
			A.setZero();
			B.setZero();
			A.block(0, 0, 3, 3).setIdentity();
			Eigen::Vector3d st;
			st.setConstant(_t);
			A.block(0, 3, 3, 3) = st.asDiagonal();
			A.block(3, 3, 3, 3).setIdentity();
			B.block(3, 0, 3, 3) = st.asDiagonal();
			/*std::cout << "A: " << std::endl;
			std::cout << A << std::endl;
			std::cout << "B: " << std::endl;
			std::cout << B << std::endl;*/
			traGenerator.mpc_init(A, B, _Q, _F, _R, _W, 0);
		}
		/* ���µ�ʽԼ�� */
		void setEqConstrain(const Vector3d& _aMax)
		{
			// ���ٶ�������(������ÿ��Ԫ��ȡ����ֵ����)
			Eigen::Vector3d ub = _aMax.cwiseAbs();
			Eigen::Vector3d lb = -_aMax.cwiseAbs();
			traGenerator.setConstrain(lb, ub);
		}
		/* ��ȡmpcԭʼ��� */
		const Eigen::Vector3d& getMpcOriOut()
		{
			return this->acc;
		}
	};

}