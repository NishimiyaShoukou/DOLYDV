/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	 TcpServer.h                                                */
/*Content summary:		TcpServer头文件 基于https://github.com/kashimAstro/SimpleNetwork.git 	*/
/*Other instructions:			*/
/*Current version:				*/
/*Author: 				*/
/*Completion date: 		*/
/*Modification record:	*/
/*Modification date       */
/* ------------------------------------------------------------------------------- */
/*    2024-11-26                V1.00        wangwentao             Create          */
#pragma once


#include <iostream>
#include <vector>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <thread>
#include <algorithm>
#include <cctype>
#include <mutex>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

using namespace std;

#define MAXPACKETSIZE 40960
#define MAX_CLIENT 1000
//#define CODA_MSG 4

struct descript_socket{
	int socket     = -1;
	string ip      = "";
	int id         = -1; 
	std::string message;
	bool enable_message_runtime = false;
};

class TCPServer
{
	public:
		int setup(int port, vector<int> opts = vector<int>());
		vector<descript_socket*> getMessage();
		void accepted();
		void Send(string msg, int id);
		void detach(int id);
		void clean(int id);
		bool is_online();
		string get_ip_addr(int id);
		string get_local_ip(void);
		int get_last_closed_sockets();
		int get_connect_num();
		void closed();

	private:
		int sockfd, n, pid;
		struct sockaddr_in serverAddress;
		struct sockaddr_in clientAddress;
		pthread_t serverThread[ MAX_CLIENT ];

		static vector<descript_socket*> newsockfd;
		static char msg[ MAXPACKETSIZE ];
		static vector<descript_socket*> Message;//[CODA_MSG];

		static bool isonline;
		static int last_closed;
		static int num_client;
		static std::mutex mt;
		static void * Task(void * argv);
};

