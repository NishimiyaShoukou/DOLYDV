
#include "main.h"
#include <unistd.h>  
#include "init.h"
#include "ServoMotor.h"
#include "Gpio.h"
#include <thread>
#include <sched.h>
#include "app.h"
#include <iostream>
#include <time.h>
#include "base.h"
#include "gui.h"
#include "Timer.h"

// 通过pthread实现多线程，�?完善



int Thread_Attr_Set( pthread_attr_t *attr, struct sched_param *sched );
#define QUIT_KEY         		(char)113
static vector<int> opts = { SO_REUSEPORT, SO_REUSEADDR };
static uint8_t g_WifiState;
// press 'q' exit all thread
// 按q退出所有程�?
extern "C" void * monthread(void *)
{

    uint8_t ch;


	while(1)
	{
        
        ch = scanKeyboard();
        
        
        printf("getkey:%d\r\n",ch);
        printf("monrun\r\n");
        if (QUIT_KEY == ch)
        {

            printf("helloworldgui\r\n");
            pthread_exit(0);
        }
 

        sleep(1);
		// sleep(2);
	}
	
}

// test
extern "C" void * testthread(void *)
{
 	int          creat_status = 0;
    pthread_t    tcp_recv_thread;
    pthread_attr_t          tcp_recv_thread_attr;
    struct sched_param          tcp_recv_thread_sched; 
    // Rate testfrq(0.5);
    Timer time_count;
	while(1)
	{
        if (g_WifiState == 0)
        {
            tcp.accepted();
        }
       // wifi connect fail
        if (g_WifiState == 1)
        {
            std::cout << "step11111111" << std::endl;
            if (isWifiConnected()) {
                g_WifiState = 0;
                std::cout << "WiFi is connected." << std::endl;
                if (tcp.setup(IP_PORT, opts) == 0)
                {
                    tcp_recv_thread_sched.sched_priority = 33; 
                    /* set priority */
                    creat_status = Thread_Attr_Set(&tcp_recv_thread_attr, &tcp_recv_thread_sched);
                    /* create thread */
                    creat_status = pthread_create(&tcp_recv_thread, \
                                            &tcp_recv_thread_attr, \
                                            tcp_server_recv, \
                                            (void *)NULL);
                    if (creat_status != 0)
                    {
                        printf("Initial thread terminating with an error\n");
                        exit(EXIT_FAILURE);
                    }	
                }
                else
                {
                    std::cout << "TCP init faild." << std::endl;
                }

    
            } else {
                g_WifiState = 1;
                std::cout << "WiFi is not connected." << std::endl;
            }
        }        
        printf("app run:%ld\r\n" ,time_count.elapsed_ms());
        time_count.reset();
        printf("wificon%d\r\n", g_WifiState);
        // printf("ip:%s\r\n", get_local_ip());
		sleep(1);
        // testfrq.sleep();
	}
	
}


int main()
{
	int          creat_status = 0;
    pthread_t    clock_thread;
	pthread_t    mon_thread;
    pthread_t    tcp_recv_thread;
    pthread_t    app_thread;
    pthread_t    gui_thread;

    pthread_attr_t          clock_thread_attr;
	pthread_attr_t          mon_thread_attr;
    pthread_attr_t          app_thread_attr;
    pthread_attr_t          tcp_recv_thread_attr;
    pthread_attr_t          gui_thread_attr;

    struct sched_param          clock_thread_sched;
	struct sched_param          mon_thread_sched;
    struct sched_param          app_thread_sched;
    struct sched_param          tcp_recv_thread_sched;
    struct sched_param          gui_thread_sched;
    

    // Timer::elapsed();
    // 实时线程，必须由 root 用户才能创建
    if (0 != getuid())
    {
        printf("Please run as root \n");
        exit(0);
    }
	// Setup Servo power control GPIO as output and set HIGH as a default value
	init_system();
	/**************************************************************************/
	/* clock task init                              		                  */
	/**************************************************************************/
    clock_thread_sched.sched_priority = 50; 
    /* set priority */
    creat_status = Thread_Attr_Set(&clock_thread_attr, &clock_thread_sched);
    /* create thread */
    creat_status = pthread_create(&clock_thread, \
                            &clock_thread_attr, \
                            clock_task, \
                            (void *)NULL);
    if (creat_status != 0)
    {
        printf("Initial thread terminating with an error\n");
        exit(EXIT_FAILURE);
    }
	/**************************************************************************/
	/* monitor task init                              		                  */
	/**************************************************************************/
    mon_thread_sched.sched_priority = 41; 
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
	/* tcp_recv task init                              		                  */
	/**************************************************************************/
   
    if (isWifiConnected()) {
        std::cout << "WiFi is connected." << std::endl;
        tcp.setup(IP_PORT, opts);
        tcp_recv_thread_sched.sched_priority = 33; 
        /* set priority */
        creat_status = Thread_Attr_Set(&tcp_recv_thread_attr, &tcp_recv_thread_sched);
        /* create thread */
        creat_status = pthread_create(&tcp_recv_thread, \
                                &tcp_recv_thread_attr, \
                                tcp_server_recv, \
                                (void *)NULL);
        if (creat_status != 0)
        {
            printf("Initial thread terminating with an error\n");
            exit(EXIT_FAILURE);
        }	

    } else {
        std::cout << "WiFi is not connected." << std::endl;
        g_WifiState = 1;
    }
 
	/**************************************************************************/
	/* gui task init                              		                  */
	/**************************************************************************/
    gui_thread_sched.sched_priority = 20; 
    /* set priority */
    creat_status = Thread_Attr_Set(&gui_thread_attr, &gui_thread_sched);
    /* create thread */
    creat_status = pthread_create(&gui_thread, \
                            &gui_thread_attr, \
                            gui_task, \
                            (void *)NULL);
    if (creat_status != 0)
    {
        printf("Initial thread terminating with an error\n");
        exit(EXIT_FAILURE);
    }
	/**************************************************************************/
	/* app task init                              		                  */
	/**************************************************************************/
    app_thread_sched.sched_priority = 40; 
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



	/**************************************************************************/
	/* Thread exit                                                             */
	/**************************************************************************/

	pthread_join(mon_thread, 0);
	/* Cancel thread */
    pthread_cancel(clock_thread);
	pthread_cancel(mon_thread);
    pthread_cancel(tcp_recv_thread);
    pthread_cancel(app_thread);
    pthread_cancel(gui_thread);
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

