#pragma once
#include "Timer.h"
#include <chrono>
class Rate {
    private:
        Timer timer;
        std::chrono::microseconds interval_us;
        std::chrono::milliseconds interval_ms;
        uint8_t use_microseconds = 0;
    public:
        Rate(double frequency);
        void reset();
        uint8_t sleep();
};
