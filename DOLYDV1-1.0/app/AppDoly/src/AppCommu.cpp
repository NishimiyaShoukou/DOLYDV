/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	 AppCommu.c                                                */
/*Content summary: 通讯应用层的TCP数据处理解析 	*/
/*Other instructions:			*/
/*Current version:				*/
/*Author: 				*/
/*Completion date: 		*/
/*Modification record:	*/
/*Modification date       */
/* ------------------------------------------------------------------------------- */
/*    2024-11-26                V1.00        wangwentao             Create          */
#include "AppCommu.h"
#include "commu.h"
#include "gui.h"
#include "base.h"
#include <iostream>
#include <csignal>
#include <ctime>
#include "ServoMotor.h"
#include "Gpio.h"
#include <thread>
#include <string>
#include "Motor.h"
TCPServer tcp;
pthread_t msg1[MAX_CLIENT];
int num_message = 0;
int time_send   = 2700;
//暂时固定指令大小为4字节
/* Process_Commu里应用 2024/4/26 wwt*/
static char receive_cmd[5] = {0}; 
static const unsigned char cmd_len = 4;
static const unsigned char receive_min_len = 6;


static char process_Comm(char *buf, unsigned char buf_len);

void close_app(int s) {
	tcp.closed();
	exit(0);
}


void * tcp_server_send(void *arg)
{
        struct descript_socket *desc = (struct descript_socket*) arg;

	while(1) {
		if(!tcp.is_online() && tcp.get_last_closed_sockets() == desc->id) {
			cerr << "Connessione chiusa: stop send_clients( id:" << desc->id << " ip:" << desc->ip << " )"<< endl;
			break;
		}
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		int hour = now->tm_hour;
		int min  = now->tm_min;
		int sec  = now->tm_sec;

		std::string date = 
			    to_string(now->tm_year + 1900) + "-" +
			    to_string(now->tm_mon + 1)     + "-" +
			    to_string(now->tm_mday)        + " " +
			    to_string(hour)                + ":" +
			    to_string(min)                 + ":" +
			    to_string(sec)                 + "\r\n";
		cerr << date << endl;
		tcp.Send(date, desc->id);
		sleep(time_send);
	}
	pthread_exit(NULL);
	return 0;
}

void * tcp_server_recv(void *)
{
	vector<descript_socket*> desc;
	char s_recv_buf[255];

	while(1)
	{

		desc = tcp.getMessage();
		for(unsigned int i = 0; i < desc.size(); i++) {
			if( desc[i] )
			{
				// if(!desc[i]->enable_message_runtime) 
				// {
				// 	desc[i]->enable_message_runtime = true;
			    //             if( pthread_create(&msg1[num_message], NULL, tcp_server_send, (void *) desc[i]) == 0) {
				// 		cerr << "ATTIVA THREAD INVIO MESSAGGI" << endl;
				// 	}
				// 	num_message++;
				// 	// start message background thread
				// }
				cout << "id:      " << desc[i]->id      << endl
				     << "ip:      " << desc[i]->ip      << endl
				     << "message: " << desc[i]->message << endl
				     << "socket:  " << desc[i]->socket  << endl
				     << "enable:  " << desc[i]->enable_message_runtime << endl;
				strcpy(s_recv_buf, desc[i]->message.c_str());
			
				process_Comm(s_recv_buf, desc[i]->message.length());
				tcp.clean(i);
			}
		}
	

		usleep(1000);
	}

}

// SARM LANGLE,RANGLE,SPEED,
static char SARM_Comand(char *buf, unsigned char buf_len)
{
	int index = 0;
	int num   = 0;
	// int ret;

	char rec_data[256] = {0};
	// char rec_cmd[10]   = {0};	

    int left_angle = 0, right_angle = 0, speed = 50;
	if (buf[index] == 0x20)
	{
		// get left angle
		while (buf[index] != 0x2c) 
		{
			if (index >= (buf_len - 1))
			{
				return 0;
			}
			rec_data[num++] = buf[index++];
		}
		rec_data[num] = '\0';
		left_angle = atoi(rec_data);
		if ((left_angle < 0) || (left_angle > SERVO_ARM_MAX_ANGLE))
		{
			return 0;
		}
		index++;
		num = 0;
		// get right angle
		while (buf[index] != 0x2c) 
		{
			if (index >= (buf_len - 1))
			{
				return 0;
			}
			rec_data[num++] = buf[index++];
		}
		rec_data[num] = '\0';
		right_angle = atoi(rec_data);
		if ((right_angle < 0) || (right_angle > SERVO_ARM_MAX_ANGLE))
		{
			return 0;
		}
		index++;
		num = 0;
		// get speed
		while (buf[index] != 0x2c) 
		{
			if (index >= (buf_len - 1))
			{
				return 0;
			}
			rec_data[num++] = buf[index++];
		}
		rec_data[num] = '\0';
		speed = atoi(rec_data);
		if ((speed < 1) || (speed > 100))
		{
			return 0;
		}

				
		ServoMotor::set(SERVO_LEFT, left_angle, speed);
	    ServoMotor::set(SERVO_RIGHT, right_angle, speed);
	}
	return 1;
}
// SPWM ML,MR,
static char SPWM_Comand(char *buf, unsigned char buf_len)
{
	int index = 0;
	int num   = 0;
	// int ret;

	char rec_data[256] = {0};
	// char rec_cmd[10]   = {0};	

    int left_pwm,right_pwm;
	if (buf[index] == 0x20)
	{
		// get left pwm
		while (buf[index] != 0x2c) 
		{
			if (index >= (buf_len - 1))
			{
				return 0;
			}
			rec_data[num++] = buf[index++];
		}
		rec_data[num] = '\0';
		left_pwm = atoi(rec_data);

		index++;
		num = 0;
		// get right pwm
		while (buf[index] != 0x2c) 
		{
			if (index >= (buf_len - 1))
			{
				return 0;
			}
			rec_data[num++] = buf[index++];
		}
	    rec_data[num] = '\0';
		right_pwm = atoi(rec_data);
		printf("SPWM");
		printf(":%d,%d",left_pwm, right_pwm);
		Motor::setPwm(LeftMotor, left_pwm);
		Motor::setPwm(RightMotor, right_pwm);
	}
	return 1;
}
static char process_Comm(char *buf, unsigned char buf_len)
{

	bool ret = 0;

	int i;


	for (i = 0; i < 4; i++)
	{
		receive_cmd[i]         = *buf++;
	}
	
	buf_len               -= 4;
	receive_cmd[4]         = '\0';


   
	switch(receive_cmd[0]) {
		case 'S':
			if (strcmp(receive_cmd, "SARM") == 0)   // SET ARM 0 DEGREE 
			{
				SARM_Comand(buf, buf_len);

				break;
				// GPIO::writePin(Pin_Servo_Left_Enable, LOW);
				// GPIO::writePin(Pin_Servo_Right_Enable, LOW);							
			}
			if (strcmp(receive_cmd, "STIM") == 0)   // SET ARM 0 DEGREE 
			{
				set_eyestate(1);
				break;
						
			}
			if (strcmp(receive_cmd, "SEYE") == 0)   // SET ARM 0 DEGREE 
			{
				set_eyestate(0);
				break;
						
			}
			if (strcmp(receive_cmd, "SPWM") == 0)   // SET ARM 0 DEGREE 
			{
				SPWM_Comand(buf, buf_len);
				break;
			}
			break;
		case 'R':
			if (strcmp(receive_cmd, "RARM") == 0)   // DISABLE ARM 
			{

				GPIO::writePin(Pin_Servo_Left_Enable, LOW);
				GPIO::writePin(Pin_Servo_Right_Enable, LOW);							
			}
			break;
		default : break;
	

	}
    return ret;
}
