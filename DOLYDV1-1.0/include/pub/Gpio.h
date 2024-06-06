#pragma once
#include <stdint.h>
#include <iostream>
#include <memory>
enum GpioType :uint8_t
{
	GPIO_INPUT = 0,
	GPIO_OUTPUT = 1,
	GPIO_PWM = 2
};

enum GpioState :bool
{
	LOW = false,
	HIGH = true,
};

enum PinId :uint8_t
{

	// >= 50 GPIO_CHIP2
	Pin_Servo_Left_Enable = 56,
	Pin_Servo_Right_Enable = 57,
	GPIO2_Pin0 = 58,
	GPIO2_Pin1 = 59,
	GPIO2_Pin2 = 60,
	GPIO2_Pin3 = 61,
	GPIO2_Pin5 = 62,
	GPIO2_Pin6 = 63,
};

enum PwmId :uint8_t
{
	Pwm_Led_Left_B = 6,
	Pwm_Led_Left_R = 7,
	Pwm_Led_Left_G = 8,
	Pwm_Led_Right_B = 9,
	Pwm_Led_Right_R = 10,
	Pwm_Led_Right_G = 11,

	Pwm_Motor_Left_L = 12,
	Pwm_Motor_Left_H = 13,
	Pwm_Motor_Right_H = 14,
	Pwm_Motor_Right_L = 15,
};
class GpioPin;

namespace GPIO
{
	// Initialize IO pin
	// state is optional for GPIO
	// return 0 = success
	// return -1 = initialized failed
	// return -2 = wrong type
	int8_t init(PinId id, GpioType type, GpioState state = GpioState::LOW);

	// Initialize PWM pin
	// return 0 = success
	// return -1 = initialized failed
	int8_t init(PwmId id);

	// return 0 success
// return -1 write failed
// return -2 undefined id
	int8_t writePin(PinId id, GpioState state);

	// return 0 success
	// return -1 write failed
	// return -2 undefined id
	int8_t writePwm(PwmId id, uint16_t value);

	GpioState readPin(std::shared_ptr<GpioPin> pin);
};
