#include "Tof.h"
#include "vl6180_pi.h"
#include "Gpio.h"
#include <thread>
static vl6180 handle_left, handle_right;
int Tof::init(int device)
{

    // disable Tof right
    GPIO::init(Pin_Tof_Right_Enable, GPIO_OUTPUT, LOW);   
    GPIO::writePin(Pin_Tof_Right_Enable, LOW);
  	std::this_thread::sleep_for(std::chrono::milliseconds(3));  
    handle_left = vl6180_initialise(device);
    if(handle_left <= 0){
		return -1;
	}
    vl6180_change_addr(handle_left, VL6180_SECOND_ADDR);
  	std::this_thread::sleep_for(std::chrono::milliseconds(3));
    GPIO::writePin(Pin_Tof_Right_Enable, HIGH);  
  	std::this_thread::sleep_for(std::chrono::milliseconds(3));
    handle_right = vl6180_initialise(device);
    if(handle_right <= 0){
		return -1;
	}

    return 1;
}

int Tof::getDistance(TofSide side)
{
    int distance = 255;
    if (side == LeftTof)
    {
        vl6180_change_device(handle_left, VL6180_SECOND_ADDR);
        distance = get_distance(handle_left);
    }
    else if (side == RightTof)
    {
        vl6180_change_device(handle_right, VL6180_DEFAULT_ADDR);
        distance = get_distance(handle_right);
    }

    return distance;
}

float Tof::getAmbientLight(TofSide side, int gain)
{
    float ambient_light;
    if (side == LeftTof)
    {
        vl6180_change_device(handle_left, VL6180_SECOND_ADDR);
        ambient_light = get_ambient_light(handle_left, (vl6180x_als_gain_t)gain);
    }
    else if (side == RightTof)
    {
        vl6180_change_device(handle_right, VL6180_DEFAULT_ADDR);
        ambient_light = get_ambient_light(handle_right, (vl6180x_als_gain_t)gain);
    }
    return ambient_light;
}


void Tof::setScaling(TofSide side, int scall)
{
    if (side == LeftTof)
    {
        vl6180_change_device(handle_left, VL6180_SECOND_ADDR);
        set_scaling(handle_left, scall);
    }
    else if (side == RightTof)
    {
        vl6180_change_device(handle_right, VL6180_DEFAULT_ADDR);
        set_scaling(handle_right, scall);
    }
}
