/*
 * @Author: Thoelc 623624394@qq.com
 * @Date: 2024-06-13 19:03:44
 * @LastEditors: Thoelc 623624394@qq.com
 * @LastEditTime: 2024-06-20 01:44:22
 * @FilePath: \DOLYDV\DOLYDV1-1.0\app\movebase\inc\PidCtrl.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*<FH+>************************************************************************/
/*File name:        PidCtrl.h                                                */
/*Content summary: Implements PID control functions for motor closed-loop control  */
/*Other instructions:            */
/*Current version:                */
/*Author:                */
/*Completion date:        */
/*Modification record:    */
/*Modification date       */
/* ------------------------------------------------------------------------------- */
/*    2024-11-26                V1.00        wangwentao             Create          */


#pragma once
#include <iostream>

enum {
    LLAST	= 0,
    LAST 	= 1,
    NOW 	= 2,

    POSITION_PID,
    DELTA_PID,
};

class PidCtrl
{
private:
    /* data */
    typedef struct    //定义pid结构体
    {
        float kp;
        float ki;
        float kd;
        float max_out;
        float err[3];
        float i_band;
        int out;
        
        float max_input;
        float min_input;

    } pid_t;

    pid_t pid_move;
    int16_t Motor_Encoder[2];
    float Target_Speed[2];
    float Current_Speed[2];
    int motor_ratio;
    int pulse_num;

    int Abs(int val);
    void getEncoderVal(void);

public:
// ratio: Motor reduction ratio
// pulse_num: Number of pulses from the encoder's magnetic ring
    PidCtrl(int ratio, int pulse_num);
    

    void PID_Reset(float kp_get,float ki_get,float kd_get);
    void Get_CurSpeed(int spd[]);
    void SetTargetSpeed(float leftspd,float rightspd);
    void PID_Controller(void);
    int Position_PID(pid_t *pid, float set, float get);
    int Incremental_PID(pid_t *pid, float set, float get);
};



