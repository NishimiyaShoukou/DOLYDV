#include "init.h"
#include "ServoMotor.h"
#include "Gpio.h"
#include "LcdControl.h"
#include <thread>
#include "app.h"
#include <iostream>


void init_system(void)
{
    init_hw();
}


void init_hw(void)
{
	// Setup Servo power control GPIO as output and set HIGH as a default value
	GPIO::init(Pin_Servo_Left_Enable, GPIO_OUTPUT, HIGH);
	GPIO::init(Pin_Servo_Right_Enable, GPIO_OUTPUT, HIGH);
	// GPIO::init(Touch_R_Input, GPIO_INPUT, HIGH);
	// GPIO::init(Touch_R_Input, GPIO_INPUT);
    GPIO::init(Pwm_Motor_Left_H);
	GPIO::init(Pwm_Motor_Left_L);
	GPIO::init(Pwm_Motor_Right_H);
	GPIO::init(Pwm_Motor_Right_L);

	// Initialize and configure servo motors
	ServoMotor::Init();
	ServoMotor::setup(SERVO_LEFT, 500, 2500, SERVO_ARM_MAX_ANGLE, false);
	ServoMotor::setup(SERVO_RIGHT, 500, 2500, SERVO_ARM_MAX_ANGLE, true);
	// LcdControl::init(LCD_12BIT);

	// LcdColorDepth depth = LcdControl::getColorDepth();
    printf("init complete!\r\n");    
}