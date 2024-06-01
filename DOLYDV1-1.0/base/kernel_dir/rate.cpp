/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	  Rate.c                                               */
/*Content summary:	ʵ������Ros::Rate�ľ�׼������ʱ������ĿǰΪms����ʵ��		*/
/*Other instructions:			*/
/*Current version:				*/
/*Author: 				*/
/*Completion date: 		*/
/*Modification record:	*/
/*Modification date       */
/* ------------------------------------------------------------------------------- */
/*    2024-09-26                V1.00        wangwentao             Create          */
/*<FH->************************************************************************/


#include "rate.h"
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>

// frequency:����ִ��Ƶ��
Rate::Rate(double frequency){
    if (frequency <= 0.0) {
        throw std::invalid_argument("Frequency must be greater than zero");
    }
    if (frequency <= 1.0) {
        printf("getfrq:%f,1",frequency);
        interval_ms = std::chrono::milliseconds(static_cast<int64_t>(1000.0 / frequency));
        use_microseconds = 0;
    } else {
        printf("getfrq:%f,2",frequency);
        interval_us = std::chrono::microseconds(static_cast<int64_t>(1000000.0 / frequency));
        use_microseconds = 1;
    }
    timer.reset();
}

// ��λʱ���
void Rate::reset() {
    timer.reset();
}

// Rate�����ʣ��ʱ����������öɣ�һ��Ҫ����
uint8_t Rate::sleep() 
{
    // printf("use_microseconds:%d", use_microseconds);
    if (use_microseconds) {
        auto elapsed = timer.elapsed_us();
        auto sleep_duration = interval_us.count() - elapsed;
        if (sleep_duration > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
        } else {
            std::cerr << "Cannot maintain desired rate! Took " << -sleep_duration << " microseconds longer than specified." << std::endl;
            timer.reset();
            return 1;
        }
    } else {
        auto elapsed = timer.elapsed_ms();
        auto sleep_duration = interval_ms.count() - elapsed;
        if (sleep_duration > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
        } else {
            std::cerr << "Cannot maintain desired rate! Took " << -sleep_duration << " milliseconds longer than specified." << std::endl;
            timer.reset();
            return 0;
        }
    }
    timer.reset();
    return 1;
}






