#pragma once
// typedef enum {
//     GAIN_20 = 0, // Actual ALS Gain of 20
//     GAIN_10,     // Actual ALS Gain of 10.32
//     GAIN_5,      // Actual ALS Gain of 5.21
//     GAIN_2_5,    // Actual ALS Gain of 2.60
//     GAIN_1_67,   // Actual ALS Gain of 1.72
//     GAIN_1_25,   // Actual ALS Gain of 1.28
//     GAIN_1,      // Actual ALS Gain of 1.01
//     GAIN_40,     // Actual ALS Gain of 40
// } vl6180x_als_gain_t;
#include <stdint.h>
#include <iostream>
enum TofSide:uint8_t
{
	LeftTof,
	RightTof,

};
namespace Tof
{
/// \param device The I2C bus to open. e.g. "1" for using /dev/i2c-1
/// return -1 init faild
    int init(int device);

    int getDistance(TofSide side); 

    float getAmbientLight(TofSide side, int gain);

    void setScaling(TofSide side, int scall);

}