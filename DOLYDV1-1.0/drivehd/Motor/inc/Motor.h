/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	  Motor.h                                               */
/*Content summary:	实现电机控制	                                   */
/*Other instructions:			        */
/*Current version:				*/
/*Author: 				*/
/*Completion date: 		*/
/*Modification record:	*/
/*Modification date       */
/* ------------------------------------------------------------------------------- */
/*    2024-09-26                V1.00        wangwentao             Create          */
/*<FH->************************************************************************/
#pragma once
#include "Gpio.h"

enum MotorOption : uint8_t
{
	LeftMotor,
	RightMotor,
	Brake,

};
namespace Motor 
{
    void init();
// The 'pwm' paramater range between 0-4095
    void setPwm(MotorOption opt, int16_t spd);
    // int getETRVal();

};

