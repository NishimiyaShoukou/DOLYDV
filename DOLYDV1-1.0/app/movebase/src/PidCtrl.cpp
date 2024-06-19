/*<FH+>************************************************************************/
/*File name:        PidCtrl.c                                                */
/*Content summary: Implements PID control functions for motor closed-loop control  */
/*Other instructions:            */
/*Current version:                */
/*Author:                */
/*Completion date:        */
/*Modification record:    */
/*Modification date       */
/* ------------------------------------------------------------------------------- */
/*    2024-11-26                V1.00        wangwentao             Create          */

#include "PidCtrl.h"
#include <math.h>
#include "Timer.h"
#include "Gpio.h"
#include "xGpio.h"
#include "Motor.h"

// ratio: Motor reduction ratio
// pulse_num: Number of pulses from the encoder's magnetic ring

PidCtrl::PidCtrl(int ratio, int pulse_num)
{
	motor_ratio = ratio;
	pulse_num = pulse_num;
	pid_move.kp = 100;
	pid_move.ki = 0.5;
	pid_move.kd = 0;
	pid_move.max_out= 4095;
	pid_move.i_band = 0;
	pid_move.out = 0;

}
/*****************
   ȡ����ֵ
****************/
	 
int PidCtrl::Abs(int val)
{
	return val>0?val:-val;
}
void PidCtrl::getEncoderVal(void)
{
   // To be implemented. Currently, there is no particularly good method to read encoder values (the current xgpio method can cause thread blocking or interfere with real-time thread issues)


}
void PidCtrl::Get_CurSpeed(int spd[])
{
	getEncoderVal();
	Current_Speed[LeftMotor] = (Motor_Encoder[LeftMotor] * 6000 / (motor_ratio * pulse_num *2));
	Current_Speed[RightMotor] = (Motor_Encoder[RightMotor] * 6000 / (motor_ratio * pulse_num *2));
	spd[0] = (int)Current_Speed[LeftMotor];
	spd[1] = (int)Current_Speed[RightMotor];

}
/// @brief �����������Ŀ���ٶ� r/min
/// @param leftspd 
/// @param rightspd 
void PidCtrl::SetTargetSpeed(float leftspd,float rightspd)
{
	Target_Speed[LeftMotor] = leftspd;
	Target_Speed[RightMotor] = rightspd;
}
/***********************
    pid�����趨
************************/
void PidCtrl::PID_Reset(float kp_get,float ki_get,float kd_get)
{
	  pid_move.kp = kp_get;
	  pid_move.ki = ki_get;
	  pid_move.kd = kd_get;
	
}
/// @brief PID control execution function. Note!!! Be very careful when debugging the motor tracks and the mechanical arm!!
/// @param none

void PidCtrl::PID_Controller(void)
{
	int cur_spd[2], i, pwm;
	Get_CurSpeed(cur_spd);


	for (i = 0; i < 2; i++)
	{
		// pwm = Position_PID(&pid_move, Target_Speed[i], Current_Speed[i]);
		// Motor::setPwm((MotorOption)i, pwm);
	}
	
}

/**************************************************************************
Function: Positional Controller
Parameters: Encoder Measurement, Target Speed
Returns: Motor PWM
Based on the positional PID formula 
pwm = Kp*e(k) + Ki*iband + Kd*[e(k) - e(k-1) + e(k-2)]

**************************************************************************/


int PidCtrl::Position_PID(pid_t *pid,float set,float get)  //pid��λʽ
{
    
    
    pid->err[NOW]=set-get;                       //�õ���ǰƫ��ֵ
	  
	 
	  pid->max_out = 4095;                           
	  pid->i_band += pid->err[NOW];             
	  pid->i_band=(pid->i_band>10000)?0:pid->i_band;    //�����޷�
	  pid->i_band=(pid->i_band<-10000)?0:pid->i_band;
	  pid->out=pid->kp*pid->err[NOW]     +
	           pid->ki*pid->i_band       +
	           pid->kd*(pid->err[NOW]-2*pid->err[LAST]+pid->err[LLAST]);
	 
	
	  pid->err[LLAST] = pid->err[LAST];
     pid->err[LAST] = pid->err[NOW];
	  pid->out=(pid->out>pid->max_out)?pid->max_out:pid->out;      //����޷�
	  pid->out=(pid->out<-(pid->max_out))?-(pid->max_out):pid->out;
    return (int)pid->out;
}

/**************************************************************************
Function: Incremental PI Controller
Parameters: Encoder Measurement, Target Speed
Returns: Motor PWM
Based on the incremental discrete PID formula 
pwm += Kp*[e(k) - e(k-1)] + Ki*e(k) + Kd*[e(k) - 2*e(k-1) + e(k-2)]
e(k) represents the current error 
e(k-1) represents the previous error, and so on 
pwm represents the incremental output
In our speed control closed-loop system, only PI control is used
pwm += Kp*[e(k) - e(k-1)] + Ki*e(k)
**************************************************************************/

int PidCtrl::Incremental_PID(pid_t *pid, float set, float get)
{   
     
       
     pid->err[NOW] = set-get;               //����ٶ�ƫ��ɲ���ֵ��ȥĿ��ֵ��
     pid->out += pid->kp*(pid->err[NOW]-pid->err[LAST])+
	             pid->ki*pid->err[NOW]                 +  //ʹ������ PI ������������ PWM��
	             pid->kd*(pid->err[NOW]-2*pid->err[LAST]+pid->err[LLAST]);
     pid->err[LLAST] = pid->err[LAST];
     pid->err[LAST] = pid->err[NOW];     //������һ��ƫ�� 
	 pid->max_out = 4095;  
	 pid->out=(pid->out > pid->max_out)?pid->max_out:pid->out;      //����޷�
	 pid->out=(pid->out<-(pid->max_out))?-(pid->max_out):pid->out;
     return pid->out;                         //�������
}