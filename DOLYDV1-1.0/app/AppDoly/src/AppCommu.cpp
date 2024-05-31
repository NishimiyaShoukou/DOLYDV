/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	 AppCommu.c                                                */
/*Content summary: 进行应用层的TCP数据处理解析 	*/
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
#include <iostream>
#include <csignal>
#include <ctime>
#include "ServoMotor.h"
#include "Gpio.h"
#include <thread>
TCPServer tcp;
pthread_t msg1[MAX_CLIENT];
int num_message = 0;
int time_send   = 2700;
//暂时确定指令固定大小为4个字节(4个字符)
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
        // tcp.accepted();
		// if (tcp.get_connect_num() == 0)
		// {
        //    usleep(20000);
		// }
		// printf("tcp...recv\n\r");
		desc = tcp.getMessage();
		for(unsigned int i = 0; i < desc.size(); i++) {
			if( desc[i] )
			{
				if(!desc[i]->enable_message_runtime) 
				{
					desc[i]->enable_message_runtime = true;
			                if( pthread_create(&msg1[num_message], NULL, tcp_server_send, (void *) desc[i]) == 0) {
						cerr << "ATTIVA THREAD INVIO MESSAGGI" << endl;
					}
					num_message++;
					// start message background thread
				}
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
				GPIO::init(Pin_Servo_Left_Enable, GPIO_OUTPUT, HIGH);
				GPIO::init(Pin_Servo_Right_Enable, GPIO_OUTPUT, HIGH);
				
		        ServoMotor::set(SERVO_LEFT, 0, 100);
	            ServoMotor::set(SERVO_RIGHT, 0, 100);	
                printf("rbuf:%s\n\r", receive_cmd);
				// GPIO::writePin(Pin_Servo_Left_Enable, LOW);
				// GPIO::writePin(Pin_Servo_Right_Enable, LOW);							
			}
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
