#include "clock.h"
#include <thread>
#include "base.h"
#include "gui.h"
#include "Timer.h"
#include "app.h"
void*  clock_task(void *)
{
    Rate loop_rate(100);
    // Timer timer_count;
    while(1)
    {
        // printf("clock:%ld\n\r", timer_count.elapsed_us());
        // timer_count.reset();
        Move_HeartTick();
        loop_rate.sleep();
    }
}

