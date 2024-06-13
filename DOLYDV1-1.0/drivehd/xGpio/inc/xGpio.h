/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	  xGpio.h                                               */
/*Content summary:	����gpiodʵ�ֵ�gpio����	                                   */
/*                  ���ٷ�����Gpio��ȡ���жϲ������µĺ�ѡ��	        */
/*                  ���ڶ��߳���Դռ��ԭ�򣬽����޸�GPIO�������Ǿ���ʹ�ùٷ�GPIO��	*/
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
/*********example:read touch sensor*********************************************************
*       xGPIO touch("gpiochip2");
*     printf("touchR:%d touchL:%d\n\r", touch.readGPIOInput(4), touch.readGPIOInput(5));
*     use encoder need "rmmod doly_drive" 2024/6
********************************************************************************************/
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
        int encoder;
        std::thread encoderThread;
        std::atomic<bool> running;
        std::atomic<int> encoderValue;
};


