
#include "main.h"
#include <unistd.h>  
// #include "init.h"
#include "ServoMotor.h"
#include "Gpio.h"
#include <thread>
#include <sched.h>
#include "AppDoly.h"
#include <iostream>
#include <time.h>
// 通过pthread实现多线程，未完善
int Thread_Attr_Set( pthread_attr_t *attr, struct sched_param *sched );

extern "C" void *hellothread(void *)
{
	// while(1)
	// {

		printf("helloworldgui\r\n");
		// sleep(2);
	// }
	
}

int main()
{
	int          creat_status = 0;
	pthread_t    gui_thread;

	pthread_attr_t          gui_thread_attr;

	struct sched_param          gui_thread_sched;


    // 实时线程，必须由 root 用户才能创建
    if (0 != getuid())
    {
        printf("Please run as root \n");
        exit(0);
    }
	// Setup Servo power control GPIO as output and set HIGH as a default value
	// init_system();
    gui_thread_sched.sched_priority = 55; 
    /* set priority */
    creat_status = Thread_Attr_Set(&gui_thread_attr, &gui_thread_sched);
    /* create thread */
    creat_status = pthread_create(&gui_thread, \
                            &gui_thread_attr, \
                            hellothread, \
                            (void *)NULL);
    if (creat_status != 0)
    {
        printf("Initial thread terminating with an error\n");
        exit(EXIT_FAILURE);
    }	
	app_task();
	// printf("input:%d" , GPIO::readPin(Touch_R_Input));

	/**************************************************************************/
	/* Thread exit                                                             */
	/**************************************************************************/

	pthread_join(gui_thread, 0);
	/* Cancel thread */
	pthread_cancel(gui_thread);
	return 0;
}


int Thread_Attr_Set( pthread_attr_t *attr, struct sched_param *sched )
{
    int iStatus = 0;
    iStatus = pthread_attr_init( attr );
    if( iStatus != 0 )
    {
        printf("[pthread_attr_init]failed.  Terminating with an error\n");
        return -1;
    }

    iStatus = pthread_attr_setinheritsched( attr, (int)PTHREAD_EXPLICIT_SCHED );
    if( iStatus != 0 )
    {
        printf("[pthread_attr_setinheritsched]failed.  Terminating with an error\n");
        return -1;
    }

    iStatus = pthread_attr_setschedpolicy( attr, SCHED_FIFO );
    if( iStatus != 0 )
    {
        printf("Thread Schedule Policy failed.  Terminating with an error\n");
        return -1;
    }
    
    iStatus = pthread_attr_setschedparam( attr, sched );
    if(iStatus != 0)
    {
        printf("[pthread_attr_setschedparam]failed.  Terminating with an error\n");
        return -1;
    }

    return 0;
}

