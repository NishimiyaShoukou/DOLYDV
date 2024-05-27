#pragma once


/* 客户端连接信息结构体 */
typedef struct t_connect_info
{
    SOCKET_SERVER fd[128];//连接客户端的链接ID，每个服务器最多允许连接128个客户端
    unsigned char num;//一共连接客户端的数目
}T_CONNECT_INFO;

/* 接收消息结构体 */
typedef struct t_tcp_server_recv_msg 
{
	unsigned char *pbuf;/* 接收数据指针 */
	int len;/* 接收数据长度 len=recv(); */
	SOCKET_SERVER conn_fd;
}T_TCP_SERVER_RECV_MSG;
/* 注册信息结构体 */
typedef struct t_server_install 
{
    int PortNum;/* 端口号 */
	T_CONNECT_INFO *pConnInfo;//客户端连接信息指针，注册时传递客户端连接信息变量的地址
    void(*pBackFunc)(T_TCP_SERVER_RECV_MSG);/* 接收线程的回调函数 */
}T_SERVER_INSTALL;

#define TCP_SER_RECV_BUFF_LEN               5

