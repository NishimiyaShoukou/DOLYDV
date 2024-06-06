#include "Motor.h"
#include "Gpio.h"

void Motor::init()
{
	GPIO::init(Pwm_Motor_Left_H);
	GPIO::init(Pwm_Motor_Left_L);
	GPIO::init(Pwm_Motor_Right_H);
	GPIO::init(Pwm_Motor_Right_L);  

    Motor::setPwm(Brake, 0);

}


void Motor::setPwm(MotorOption opt, int16_t spd)
{

    switch(opt)
    {
        case LeftMotor:
        {
            if (spd >= 0)
            {
                GPIO::writePwm(Pwm_Motor_Left_H, spd);
                GPIO::writePwm(Pwm_Motor_Left_L, 0);   
            }
            else
            {

                GPIO::writePwm(Pwm_Motor_Left_H, 0);
                GPIO::writePwm(Pwm_Motor_Left_L, -spd);                 
            }
        
            break;
        }
        case RightMotor:
        {
            if (spd >= 0)
            {
                GPIO::writePwm(Pwm_Motor_Right_H, spd);
                GPIO::writePwm(Pwm_Motor_Right_L, 0);   
            }
            else
            {

                GPIO::writePwm(Pwm_Motor_Right_H, 0);
                GPIO::writePwm(Pwm_Motor_Right_L, -spd);                 
            }
            break;
        }
        case Brake:
        {
            GPIO::writePwm(Pwm_Motor_Left_H, 0);
            GPIO::writePwm(Pwm_Motor_Left_L, 0);  
            GPIO::writePwm(Pwm_Motor_Right_H, 0);
            GPIO::writePwm(Pwm_Motor_Right_L, 0); 
            break;
        }
        default: break;
      
    }


}
