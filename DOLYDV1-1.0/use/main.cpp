
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
#include <base.h>
// 通过pthread实现多线程，未完善
int Thread_Attr_Set( pthread_attr_t *attr, struct sched_param *sched );
#define QUIT_KEY         		(char)113

// press 'q' exit all thread
// 按q退出所有程序
extern "C" void *monthread(void *)
{

    uint8_t ch;
	while(1)
	{
        
        ch = scanKeyboard();
        sleep(1);
        printf("getkey:%d\r\n",ch);
        if (QUIT_KEY == ch)
        {

            printf("helloworldgui\r\n");
            pthread_exit(0);
        }
		// sleep(2);
	}
	
}

// test
extern "C" void *testthread(void *)
{
  
	while(1)
	{
        
        printf("app run\r\n");
		sleep(2);
	}
	
}
int main()
{
	int          creat_status = 0;
	pthread_t    mon_thread;
    pthread_t    app_thread;

	pthread_attr_t          mon_thread_attr;
    pthread_attr_t          app_thread_attr;

	struct sched_param          mon_thread_sched;
    struct sched_param          app_thread_sched;


    // 实时线程，必须由 root 用户才能创建
    if (0 != getuid())
    {
        printf("Please run as root \n");
        exit(0);
    }
	// Setup Servo power control GPIO as output and set HIGH as a default value
	// init_system();

	/**************************************************************************/
	/* monitor task init                              		                  */
	/**************************************************************************/
    mon_thread_sched.sched_priority = 55; 
    /* set priority */
    creat_status = Thread_Attr_Set(&mon_thread_attr, &mon_thread_sched);
    /* create thread */
    creat_status = pthread_create(&mon_thread, \
                            &mon_thread_attr, \
                            monthread, \
                            (void *)NULL);
    if (creat_status != 0)
    {
        printf("Initial thread terminating with an error\n");
        exit(EXIT_FAILURE);
    }

	/**************************************************************************/
	/* app task init                              		                  */
	/**************************************************************************/
    app_thread_sched.sched_priority = 54; 
    /* set priority */
    creat_status = Thread_Attr_Set(&app_thread_attr, &app_thread_sched);
    /* create thread */
    creat_status = pthread_create(&app_thread, \
                            &app_thread_attr, \
                            testthread, \
                            (void *)NULL);
    if (creat_status != 0)
    {
        printf("Initial thread terminating with an error\n");
        exit(EXIT_FAILURE);
    }		
	// app_task();
	// printf("input:%d" , GPIO::readPin(Touch_R_Input));

	/**************************************************************************/
	/* Thread exit                                                             */
	/**************************************************************************/

	pthread_join(mon_thread, 0);
	/* Cancel thread */
	pthread_cancel(mon_thread);
    pthread_cancel(app_thread);
    printf("All threads have exited. \n");
    exit(0);
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

