/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	  xGpio.h                                               */
/*Content summary:	基于gpiod实现的gpio操作	                                   */
 /*                  （官方关于Gpio读取和中断不完善下的候补选择）	        */
/*Other instructions:			        */
/*Current version:				*/
/*Author: 				*/
/*Completion date: 		*/
/*Modification record:	*/
/*Modification date       */
/* ------------------------------------------------------------------------------- */
/*    2024-09-26                V1.00        wangwentao             Create          */
/*<FH->************************************************************************/
#include "xGpio.h"
#include <iostream>
#include <chrono>

xGPIO::xGPIO(const std::string &chipname) {
    chip = gpiod_chip_open_by_name(chipname.c_str());
    if (!chip) {
        std::cerr << "Failed to open GPIO chip: " << chipname << std::endl;
    }
    running = false;
    encoderValue = 0;
}

xGPIO::~xGPIO() {
    if (running) {
        stopEncoder();
    }
    if (chip) {
        gpiod_chip_close(chip);
    }
}

int xGPIO::readGPIOInput(int line) {
    struct gpiod_line *gpio_line = gpiod_chip_get_line(chip, line);
    if (!gpio_line) {
        std::cerr << "Failed to get GPIO line: " << line << std::endl;
        return -1;
    }

    if (gpiod_line_request_input(gpio_line, "gpio_read") < 0) {
        std::cerr << "Failed to request line as input: " << line << std::endl;
        return -1;
    }

    int value = gpiod_line_get_value(gpio_line);
    if (value < 0) {
        std::cerr << "Failed to read value from line: " << line << std::endl;
    }

    gpiod_line_release(gpio_line);
    return value;
}

void xGPIO::startEncoder(int lineA, int lineB) {
    if (running) {
        std::cerr << "Encoder is already running" << std::endl;
        return;
    }

    running = true;
    encoderThread = std::thread(&xGPIO::encoderThreadFunction, this, lineA, lineB);
}

void xGPIO::encoderThreadFunction(int lineA, int lineB) {
    struct gpiod_line *gpio_lineA = gpiod_chip_get_line(chip, lineA);
    struct gpiod_line *gpio_lineB = gpiod_chip_get_line(chip, lineB);

    if (!gpio_lineA || !gpio_lineB) {
        std::cerr << "Failed to get GPIO lines: " << lineA << ", " << lineB << std::endl;
        running = false;
        return;
    }

    if (gpiod_line_request_both_edges_events(gpio_lineA, "encoder") < 0 ||
        gpiod_line_request_both_edges_events(gpio_lineB, "encoder") < 0) {
        std::cerr << "Failed to request both edges events for lines: " << lineA << ", " << lineB << std::endl;
        running = false;
        return;
    }

    struct gpiod_line_event eventA, eventB;
    int lastA = gpiod_line_get_value(gpio_lineA);
    int lastB = gpiod_line_get_value(gpio_lineB);

    while (running) {
        int retA = gpiod_line_event_wait(gpio_lineA, nullptr);
        int retB = gpiod_line_event_wait(gpio_lineB, nullptr);

        if (retA == 1) {
            gpiod_line_event_read(gpio_lineA, &eventA);
        }

        if (retB == 1) {
            gpiod_line_event_read(gpio_lineB, &eventB);
        }

        int newA = gpiod_line_get_value(gpio_lineA);
        int newB = gpiod_line_get_value(gpio_lineB);

        if (newA != lastA || newB != lastB) {
            // 根据编码器的状态转换表更新编码器值
            if (lastA == 0 && newA == 1) {
                if (lastB == 0 && newB == 0) encoderValue--;
                if (lastB == 1 && newB == 1) encoderValue++;
            } else if (lastA == 1 && newA == 0) {
                if (lastB == 0 && newB == 0) encoderValue++;
                if (lastB == 1 && newB == 1) encoderValue--;
            } else if (lastB == 0 && newB == 1) {
                if (lastA == 0 && newA == 0) encoderValue++;
                if (lastA == 1 && newA == 1) encoderValue--;
            } else if (lastB == 1 && newB == 0) {
                if (lastA == 0 && newA == 0) encoderValue--;
                if (lastA == 1 && newA == 1) encoderValue++;
            }

            lastA = newA;
            lastB = newB;
        }

        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    gpiod_line_release(gpio_lineA);
    gpiod_line_release(gpio_lineB);
}

int xGPIO::getEncoderValue() {
    return encoderValue.load();
}

void xGPIO::stopEncoder() {
    running = false;
    if (encoderThread.joinable()) {
        encoderThread.join();
    }
}
