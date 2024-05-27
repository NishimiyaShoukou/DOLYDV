#include "AppDoly.h"
#include <iostream>
#include "base.h"
#include "ServoMotor.h"
#include "Gpio.h"
#include "LcdControl.h"
#include <thread>
#include "eye.h"
using namespace std;
 
void app_task(void)
{
    int a;
    cout << "app_task_run" << endl;
	// base_task();
	GPIO::init(Pin_Servo_Left_Enable, GPIO_OUTPUT, HIGH);
	GPIO::init(Pin_Servo_Right_Enable, GPIO_OUTPUT, HIGH);

	GPIO::init(Pwm_Led_Left_B);
	GPIO::init(Pwm_Led_Left_R);
	GPIO::init(Pwm_Led_Left_G);
	GPIO::init(Pwm_Led_Right_B);
	GPIO::init(Pwm_Led_Right_G);
	GPIO::init(Pwm_Led_Right_R);

	gui_task();
	// Setup needs channel, bandwitdh range, max angle and working direction parameters
	// Setup ignores the 'max angle' parameter for both arm servos, however they are already defined internally.
		// Initialize and configure servo motors
	ServoMotor::Init();
	ServoMotor::setup(SERVO_LEFT, 500, 2500, SERVO_ARM_MAX_ANGLE, false);
	ServoMotor::setup(SERVO_RIGHT, 500, 2500, SERVO_ARM_MAX_ANGLE, true);
    printf("%d", SERVO_RIGHT);
	// Sets servo zero positions
	// The 'speed' paramater range between 1-100
	ServoMotor::set(SERVO_LEFT, 0, 100);
	ServoMotor::set(SERVO_RIGHT, 0, 100);
	GPIO::writePwm(Pwm_Led_Left_R, 4095);
    GPIO::writePwm(Pwm_Led_Left_B, 835);
	GPIO::writePwm(Pwm_Led_Left_G, 4095);
	GPIO::writePwm(Pwm_Led_Right_R, 4095);
	GPIO::writePwm(Pwm_Led_Right_G, 4095);
	GPIO::writePwm(Pwm_Led_Right_B, 835);
		ServoMotor::set(SERVO_LEFT, 100, 100);
	ServoMotor::set(SERVO_RIGHT, 100, 100);
	// wait to get zero position
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	GPIO::writePwm(Pwm_Motor_Left_H, 0);
	GPIO::writePwm(Pwm_Motor_Right_L, 0);

	// Sets servo positions
	// The 'speed' paramater range between 1-100
	// ServoMotor::set(SERVO_LEFT, 90, 1);
	// ServoMotor::set(SERVO_RIGHT, 90, 1);

	// wait
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	ServoMotor::set(SERVO_LEFT, 100, 60);
	ServoMotor::set(SERVO_RIGHT, 100, 60);
	// // ServoMotor::set(SERVO_LEFT, SERVO_ARM_MAX_ANGLE, 100);
	// // ServoMotor::set(SERVO_RIGHT, SERVO_ARM_MAX_ANGLE, 100);

	// // wait servo
	// std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	// disable servo power
	GPIO::writePin(Pin_Servo_Left_Enable, LOW);
	GPIO::writePin(Pin_Servo_Right_Enable, LOW);

   
}