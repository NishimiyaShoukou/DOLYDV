/*
 * @Author: Thoelc 623624394@qq.com
 * @Date: 2024-04-09 19:01:44
 * @LastEditors: Thoelc 623624394@qq.com
 * @LastEditTime: 2024-04-09 19:03:54
 * @FilePath: \DOLYDV1-1.0\use\init\main.cpp
 * @Description: ??????,???`customMade`, ??koroFileHeader???? ????: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ServoMotor.h"
#include "Gpio.h"
#include <thread>
#include "AppDoly.h"
/// <summary>
/// This program demonstrates how to setup and control servos,
/// Also this program requires pthread, ServoMotor, Gpio, Timer libraries
/// ServoMotor, Gpio, Timer are part of Project Doly, libararies and headers are located under '/Doly'
/// Do not forget to Copy and Link related libraries.
/// </summary>

int main()
{
	// Setup Servo power control GPIO as output and set HIGH as a default value
	GPIO::init(Pin_Servo_Left_Enable, GPIO_OUTPUT, HIGH);
	GPIO::init(Pin_Servo_Right_Enable, GPIO_OUTPUT, HIGH);
    GPIO::init(Pwm_Motor_Left_H);
	GPIO::init(Pwm_Motor_Left_L);
	GPIO::init(Pwm_Motor_Right_H);
	GPIO::init(Pwm_Motor_Right_L);

	// Initialize and configure servo motors
	ServoMotor::Init();
	app_task();
	// Setup needs channel, bandwitdh range, max angle and working direction parameters
	// Setup ignores the 'max angle' parameter for both arm servos, however they are already defined internally.
	ServoMotor::setup(SERVO_LEFT, 500, 2500, SERVO_ARM_MAX_ANGLE, false);
	ServoMotor::setup(SERVO_RIGHT, 500, 2500, SERVO_ARM_MAX_ANGLE, true);

	// Sets servo zero positions
	// The 'speed' paramater range between 1-100
	ServoMotor::set(SERVO_LEFT, 0, 100);
	ServoMotor::set(SERVO_RIGHT, 0, 100);
    // GPIO::writePwm(Pwm_Motor_Left_H, 1000);
	// GPIO::writePwm(Pwm_Motor_Left_L, 0);
	//     GPIO::writePwm(Pwm_Motor_Right_H, 0);
	// GPIO::writePwm(Pwm_Motor_Right_L, 1000);
	// wait to get zero position
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
GPIO::writePwm(Pwm_Motor_Left_H, 0);
GPIO::writePwm(Pwm_Motor_Right_L, 0);
	ServoMotor::set(SERVO_LEFT, 50, 100);
	ServoMotor::set(SERVO_RIGHT, 50, 100);
	// Sets servo positions
	// The 'speed' paramater range between 1-100
	// ServoMotor::set(SERVO_LEFT, 90, 1);
	// ServoMotor::set(SERVO_RIGHT, 90, 1);

	// wait
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	// // ServoMotor::set(SERVO_LEFT, SERVO_ARM_MAX_ANGLE, 100);
	// // ServoMotor::set(SERVO_RIGHT, SERVO_ARM_MAX_ANGLE, 100);

	// // wait servo
	// std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	// disable servo power
	GPIO::writePin(Pin_Servo_Left_Enable, LOW);
	GPIO::writePin(Pin_Servo_Right_Enable, LOW);

	return 0;
}