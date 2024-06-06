#include "init.h"
#include "ServoMotor.h"
#include "Gpio.h"
#include "LcdControl.h"
#include <thread>
#include "app.h"
#include "Timer.h"
#include <iostream>
#include "Motor.h"
Timer tim;

void init_system(void)
{
    init_hw();
}


void init_hw(void)
{
	// Setup Servo power control GPIO as output and set HIGH as a default value
	tim.reset();
	GPIO::init(Pin_Servo_Left_Enable, GPIO_OUTPUT, HIGH);
	GPIO::init(Pin_Servo_Right_Enable, GPIO_OUTPUT, HIGH);
	// GPIO::init(Touch_R_Input, GPIO_INPUT, HIGH);
	// GPIO::init(Touch_R_Input, GPIO_INPUT);
	Motor::init();

	GPIO::init(Pwm_Led_Left_B);
	GPIO::init(Pwm_Led_Left_R);
	GPIO::init(Pwm_Led_Left_G);
	GPIO::init(Pwm_Led_Right_B);
	GPIO::init(Pwm_Led_Right_G);
	GPIO::init(Pwm_Led_Right_R);

	// Initialize and configure servo motors
	ServoMotor::Init();
	ServoMotor::setup(SERVO_LEFT, 500, 2500, SERVO_ARM_MAX_ANGLE, false);
	ServoMotor::setup(SERVO_RIGHT, 500, 2500, SERVO_ARM_MAX_ANGLE, true);
	// LcdControl::init(LCD_12BIT);
	GPIO::writePwm(Pwm_Led_Left_R, 4000);
    GPIO::writePwm(Pwm_Led_Left_B, 4000);
	GPIO::writePwm(Pwm_Led_Left_G, 4000);
	GPIO::writePwm(Pwm_Led_Right_R, 4000);
	GPIO::writePwm(Pwm_Led_Right_G, 4000);
	GPIO::writePwm(Pwm_Led_Right_B, 4000);
	// LcdColorDepth depth = LcdControl::getColorDepth();
    printf("init complete!%ld\r\n" , tim.elapsed_ms());    
}