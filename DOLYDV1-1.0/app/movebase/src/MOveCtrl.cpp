#include "MoveCtrl.h"
#include <semaphore.h>
#include "base.h"
#include "gui.h"
#include "Timer.h"
#include "Gpio.h"
#include "xGpio.h"
#include "Motor.h"
#include "Tof.h"
static sem_t move_task_sem;
xGPIO EtrLeft("gpiochip0");
void Move_HeartTick()
{
    // 10ms period
    sem_post(&move_task_sem); 
} 

void* move_robot_task(void* arg)
{
    // Timer timer_count;
    uint8_t gpio_tog;
    GPIO::init(GPIO2_Pin0, GPIO_OUTPUT, LOW);
    Tof::init(6);
    while(1)
    {
        sem_wait(&move_task_sem);
        // EtrLeft.stopEncoder();
        // printf("encode:%d\n\r",EtrLeft.getEncoderValue());
        // EtrLeft.startEncoder(13,6);
        /* test */
        // gpio_tog = 1 - gpio_tog;
        // if (gpio_tog)
        // {
        //     GPIO::writePin(GPIO2_Pin0, LOW);
        // }
        // else
        // {
        //     GPIO::writePin(GPIO2_Pin0, HIGH);
        // }
     
          printf("disl:%d disr:%d\n\r",Tof::getDistance(LeftTof), Tof::getDistance(RightTof));
        // record time
        // printf("move_clock:%ld\n\r", timer_count.elapsed_us());
        // timer_count.reset();
    }
    
}
