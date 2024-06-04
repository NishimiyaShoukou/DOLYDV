/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	  xGpio.h                                               */
/*Content summary:	基于gpiod实现的gpio操作	                                   */
/*                  （官方关于Gpio读取和中断不完善下的候补选择）	        */
/*                  由于多线程资源占用原因，进行修改GPIO操作还是尽量使用官方GPIO库	*/
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

#include <gpiod.h>
#include <string>
#include <thread>
#include <atomic>

class xGPIO {
    public:
        xGPIO(const std::string &chipname);
        ~xGPIO();

        int readGPIOInput(int line);
        void startEncoder(int lineA, int lineB);
        int getEncoderValue();
        void stopEncoder();

    private:
        void encoderThreadFunction(int lineA, int lineB);

        struct gpiod_chip *chip;
        std::thread encoderThread;
        std::atomic<bool> running;
        std::atomic<int> encoderValue;
};


