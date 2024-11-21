#pragma once
#include "Body.h"
#include "mpcCal.h"
#include "PIDmethod.h"
#include "LegCtrl.h"
#include "multiCircle.h"
#include <iostream>

using namespace Eigen;

namespace Quadruped
{
    // ����ƽ���������״̬
    typedef struct _balanceState
    {
        // ����״̬
        Vector3d p = Vector3d::Zero();
        Vector3d p_dot = Vector3d::Zero();
        Vector3d r = Vector3d::Zero();
        Vector3d r_dot = Vector3d::Zero();
        // ĩ��ִ����״̬
        Vector3d pe = Vector3d::Zero();
        Vector3d pe_dot = Vector3d::Zero();
        
    } balanceState;

    class CtrlBase
    {
    protected:

    public:
        // ����ƽ���������״̬����
        balanceState targetBalanceState;
        balanceState currentBalanceState;
        // �����ƵĻ����˱���
        Body* bodyObject;
        // �Ȳ�������
        LegCtrl* legsCtrl[4];
        // ����ѧģ�;���
        MatrixXd dynamicLeft;
        MatrixXd dynamicRight;
        // mpc���������
        MatrixXd mpcOut;
        // mpc����������
        MatrixXd A;
        MatrixXd B;
        // ������Ȩ�ز���
        MatrixXd Q; // ״̬Ȩ�ؾ���
        MatrixXd F; // �ն˲�������
        MatrixXd R; // ����Ȩ�ؾ���
        MatrixXd W; // ����ƽ������
        // Լ������
        MatrixXd lb; // ����Լ��
        MatrixXd ub;
        MatrixXd cA; // boxԼ������
        MatrixXd Alb; // boxԼ����Ե
        MatrixXd Aub;
        // ״̬��
        VectorXd y;
        VectorXd x;
        // ��������
        double dt;
        bool is_init = false;

        // ���캯��
        CtrlBase(Body* _obj, LegCtrl* _legsCtrl[4], int timeStep)
        {
            bodyObject = _obj;
            for (int i = 0; i < 4; i++)
            {
                this->legsCtrl[i] = _legsCtrl[i];
            }
            this->dt = static_cast<double>(timeStep) * 0.001;
        }
        // ����Ȩ�ز���
        virtual void importWeight(const VectorXd& _Q, const VectorXd& _F, const VectorXd& _R, const VectorXd& _W) = 0;
        // ���¶���ѧģ��
        virtual void updateDynamic() = 0;
        // ���µ�ǰ״̬
        virtual void updateBalanceState() = 0;
        // ִ��mpc������
        virtual void mpc_adjust(const VectorX<bool>& _enList) = 0;
    };

    class QpCtrl : public CtrlBase {
    private:

    public:
        // ������ƽ�������
        mpcCal<6, 12, 20, 1, 5> balanceController;
        double u = 2;// Ħ��ϵ��
        double force_c = 200;// �������

        // ���ڻ���λ�ص�pid
        PIDmethod linPID[3];
        PIDmethod angPID[3];

        // ���캯��
        QpCtrl(Body* _obj, LegCtrl* _legsCtrl[4], int timeStep):CtrlBase(_obj, _legsCtrl, timeStep)
        {
            dynamicLeft.resize(6, 12);
            dynamicRight.resize(6, 6);
            mpcOut.resize(3, 4);
            A.resize(6, 6);
            B.resize(6, 12);
            Q.resize(6, 6);
            F.resize(6, 6);
            R.resize(12, 12);
            W.resize(12, 12);
            lb.resize(12, 1);
            ub.resize(12, 1);
            cA.resize(20,12);
            Alb.resize(20, 1);
            Aub.resize(20, 1);
            y.resize(6);
            x.resize(6);

            dynamicRight.setZero();
            dynamicLeft.block<3, 3>(0, 0).setIdentity();
            dynamicLeft.block<3, 3>(0, 3).setIdentity();
            dynamicLeft.block<3, 3>(0, 6).setIdentity();
            dynamicLeft.block<3, 3>(0, 9).setIdentity();
            mpcOut.setZero();
            A.setZero();
            B.setZero();
            Q.setZero();
            R.setZero();
            lb.setConstant(-force_c);
            ub.setConstant(force_c);
            cA.setZero();

            // unitree constrain
            Eigen::Matrix<double, 5, 3> _cA;
            _cA.setZero();
            _cA << 1, 0, u, -1, 0, u, 0, 1, u, 0, -1, u, 0, 0, 1;
            cA.block<5, 3>(0, 0) = _cA;
            cA.block<5, 3>(5, 3) = _cA;
            cA.block<5, 3>(10, 6) = _cA;
            cA.block<5, 3>(15, 9) = _cA;
            Alb.setZero();
            Aub.setConstant(100000.);
        }
        // ���»����˶���ѧ���̣�����Ϊ left*[f] = right��
        void updateDynamic() override;
        // ����Ȩ�ز���
        void importWeight(const VectorXd& _Q, const VectorXd& _F, const VectorXd& _R, const VectorXd& _W) override;
        void importPDparam(const Vector<double, 9>& lin,const Vector<double, 9>& ang);
        // ���µ�ǰ״̬
        void updateBalanceState() override;
        // �����ն�Ŀ��
        void setPositionTarget(const Vector3d& _p,const Vector3d& _r);
        void setVelocityTarget(const Vector3d& _p_dot,const Vector3d& _r_dot);
        // ִ��mpc������
        void mpc_adjust(const VectorX<bool>& _enList) override;
        // �����Ȳ��Ӵ�Լ��
        void setContactConstrain(const Vector4i& _contact);
        // ֱ�������������
        void setLegsForce(const Eigen::Matrix<double, 3, 4>& _force);
    };

    void QpCtrl::updateDynamic()
    {
        for (int i = 0; i < 4; i++)
        {
            //dynamicLeft.block<3, 3>(0, i * 3) = Rsb_c;
            Vector3d Pbi = Vector3d::Zero();
            Pbi = bodyObject->Rsb_c * (bodyObject->currentBodyState.leg_b[i].Position - bodyObject->P);
            //Pbi = (currentBodyState.leg_b[i].Position - Pb);
            dynamicLeft.block<3, 3>(3, i * 3) = bodyObject->v3_to_m3(Pbi);
        }
        dynamicRight.block<3, 3>(0, 0) = bodyObject->M;
        dynamicRight.block<3, 3>(3, 3) = bodyObject->Rsb_c * bodyObject->I * bodyObject->Rsb_c.transpose();
    }

    void QpCtrl::importWeight(const VectorXd& _Q, const VectorXd& _F, const VectorXd& _R, const VectorXd& _W)
    {
        for (int i = 0; i < 6; i++)
        {
            Q(i, i) = _Q(i);
            F(i, i) = _F(i);
        }
        for (int j = 0; j < 12; j++)
        {
            R(j, j) = _R(j);
            W(j, j) = _W(j);
        }
    }

    void QpCtrl::importPDparam(const Vector<double, 9>& lin, const Vector<double, 9>& ang)
    {
        for (int i = 0; i < 3; i++)
        {
            linPID[i].Params_Config(lin(0 + i * 3), 0, lin(1 + i * 3), 0, abs(lin(2 + i * 3)), -abs(lin(2 + i * 3)));
            angPID[i].Params_Config(ang(0 + i * 3), 0, ang(1 + i * 3), 0, abs(ang(2 + i * 3)), -abs(ang(2 + i * 3)));
        }
    }

    void QpCtrl::updateBalanceState()
    {
        currentBalanceState.p = bodyObject->currentWorldState.dist;
        currentBalanceState.p_dot = bodyObject->currentWorldState.linVel_xyz;
        currentBalanceState.r = bodyObject->currentBodyState.Ang_xyz;
        currentBalanceState.r_dot = bodyObject->currentWorldState.angVel_xyz;
    }

    void QpCtrl::setPositionTarget(const Vector3d& _p, const Vector3d& _r)
    {
        targetBalanceState.p = _p;
        targetBalanceState.r = _r;
    }

    void QpCtrl::setVelocityTarget(const Vector3d& _p_dot, const Vector3d& _r_dot)
    {
        targetBalanceState.p_dot = _p_dot;
        targetBalanceState.r_dot = _r_dot;
    }

    void QpCtrl::setContactConstrain(const Vector4i& _contact)
    {
        Eigen::Matrix<double, 5, 3> _cA;
        _cA.setZero();
        Eigen::Matrix<double, 5, 1> _Aub;
        _Aub.setZero();
        // �����Ȳ����أ�������Լ������
        for (int i = 0; i < 4; i++)
        {
            if (_contact(i) == 1)
            {
                _cA << 1, 0, u, -1, 0, u, 0, 1, u, 0, -1, u, 0, 0, 1;
                _Aub.setConstant(100000.);
            }
            else
            {
                _cA << 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
                _Aub.setZero();
            }
            this->cA.block<5, 3>(5 * i, 3 * i) = _cA;
            this->Aub.block<5, 1>(5 * i, 0) = _Aub;
        }
    }

    void QpCtrl::mpc_adjust(const VectorX<bool>& _enList)
    {
        static multiCircle angC[3] = { multiCircle(3.1415926),multiCircle(3.1415926),multiCircle(3.1415926) };
        for (int i = 0; i < 3; i++)
        {
            if (_enList(2 * i) == true)
            {
                linPID[i].target = targetBalanceState.p(i);
                linPID[i].current = currentBalanceState.p(i);
                linPID[i].Adjust(0, currentBalanceState.p_dot(i));
                targetBalanceState.p_dot(i) = linPID[i].out;
            }

            if (_enList(2 * i + 1) == true)
            {
                angPID[i].target = targetBalanceState.r(i);
                angPID[i].current = angC[i].f(currentBalanceState.r(i));
                angPID[i].Adjust(0, bodyObject->currentBodyState.angVel_xyz(i));
                targetBalanceState.r_dot(i) = angPID[i].out;
                if (i == 2)
                {
                    targetBalanceState.r_dot = bodyObject->Rsb_c * targetBalanceState.r_dot;
                }
            }
        }

        B = dynamicRight.inverse() * dynamicLeft;
        balanceController.setConstrain(lb, ub);
        balanceController.setBoxConstrain(cA, Alb, Aub);
        y.block<3, 1>(0, 0) = targetBalanceState.p_dot;
        y.block<3, 1>(3, 0) = targetBalanceState.r_dot;
        x.block<3, 1>(0, 0) = currentBalanceState.p_dot;
        x.block<3, 1>(3, 0) = currentBalanceState.r_dot;
        balanceController.mpc_update(y, x, 100, 0.002);
        balanceController.mpc_init(A, B, Q, F, R, W, dt);
        balanceController.mpc_solve();
        for (int i = 0; i < 4; i++)
        {
            this->mpcOut.col(i) = -bodyObject->Rsb_c.transpose() * balanceController.getOutput().block<3, 1>(3 * i, 0);
            //this->mpcOut.col(i) = -balanceController.getOutput().block<3, 1>(3 * i, 0);
        }
    }

    void QpCtrl::setLegsForce(const Eigen::Matrix<double, 3, 4>& _force)
    {
        for (int i = 0; i < 4; i++)
        {
            this->legsCtrl[i]->setEndForceTar(_force.col(i));
        }
    }
}
