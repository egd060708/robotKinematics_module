#ifndef _GAITCTRL_H
#define _GAITCTRL_H

#include "Leg.h"
#include "Body.h"

typedef struct _GaitS {
	double Tgait;// ��̬������
	double Tstance;// ��˴�������
	double Tswing;// ��˰ڶ�����
	double k;// ����ռ��ϵ��[0��1]
	double bias[4];// ��̬ƫ����λ(����������ڶ���)
	double phase[4];// ��̬��ǰ��λ(�������ģʽ����)

	int contact[4];// �Ƿ񴥵�
	int last_contact[4];// ��һ�δ������

	double cmd[4];// �����˶�ָ���άƽ��+һά��ת+һά��̬�߶�
	double Pstart[4][3];// �����ʼλ��
	double Pend[4][3];// �����ֹλ��
	Body* robot;// �����˶���

	double t;// ��ǰϵͳʱ��
	double t_start;// ��̬���ڿ�ʼʱ��

	double End_Pos[4][3];// ���ĩ��λ��
	double End_Vel[4][3];// ���ĩ���ٶ�

	bool is_first;// �Ƿ��״����в�̬

	double R[4];// �ȵ�ת��뾶
	double theta[4];// �ȵ�λ�ü�����Ƕ�
}GaitS;

void InitGaitCtrl(GaitS* _gait, Body* _robot, double _Tgait, double _k, double _bias[4]);
void SetGaitCmd(GaitS* _gait, double _cmd[4], double _slope[3]);
void PhaseGen(GaitS* _gait, double real_t);
void StanceGait(GaitS* _gait, int idx);
void SwingGait(GaitS* _gait, int idx);
void GaitGen(GaitS* _gait);
void GaitRestart(GaitS* _gait, double real_t);


double StraightXY(double _end, double _start, double _phase);
double StraightVxy(double _end, double _star, double _period);
double CycloidXY(double _end, double _start, double _phase);
double CycloidZ(double _height, double _phase);
double CycloidVxy(double _end, double _start, double _phase, double _period);
double CycloidVz(double _height, double _phase, double _period);


#endif
