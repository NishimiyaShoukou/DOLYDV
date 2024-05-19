#include "main.h"
// #include "init.h"
#include "ServoMotor.h"
#include "Gpio.h"
#include <thread>
#include "AppDoly.h"
#include <iostream>
/// <summary>
/// This program demonstrates how to setup and control servos,
/// Also this program requires pthread, ServoMotor, Gpio, Timer libraries
/// ServoMotor, Gpio, Timer are part of Project Doly, libararies and headers are located under '/Doly'
/// Do not forget to Copy and Link related libraries.
/// </summary>

int main()
{
	// Setup Servo power control GPIO as output and set HIGH as a default value
	// init_system();
	app_task();
	// printf("input:%d" , GPIO::readPin(Touch_R_Input));


	return 0;
}