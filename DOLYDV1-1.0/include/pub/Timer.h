#pragma once
#include <iostream>
#include <chrono>

class Timer
{
    public:
        Timer() : beg_(clock_::now()) {}
        void reset();
        //returns elapsed seconds
        const double elapsed();
        //returns elapsed milliseconds
        const int64_t elapsed_ms();
        //retruns elapsed microsecoonds
        const int64_t elapsed_us();

    private:
        typedef std::chrono::high_resolution_clock clock_;
        typedef std::chrono::duration<double, std::ratio<1> > second_;
        typedef std::chrono::duration<double, std::milli > millis_;
        typedef std::chrono::duration<double, std::micro > micros_;
        std::chrono::time_point<clock_> beg_;
};

