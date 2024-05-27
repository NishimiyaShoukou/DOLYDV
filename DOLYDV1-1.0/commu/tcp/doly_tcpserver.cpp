#include "doly_tcpserver.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>

using namespace std;
#define IPPORT 1234

static unsigned char install_cnt = 0;/* 用户已经注册的端口数目 */

unsigned char tcp_server_install(T_SERVER_INSTALL install_msg)
{
    int i;
    //unsigned int iAddrLen    = 0;
    unsigned int uiReUse     = 0;
    unsigned int uiOptLen    = 0;   
    SOCKET_SERVER iSocket;/* socket的描述符 */
    struct sockaddr_in  tSocketAddr; /* socket的IP地址信息 */
    
    if (install_cnt>=TCP_SER_MAX_PORT_NUM)
    {
        return (unsigned char)0xff;
    }
    else
    {
        //do nothing
    }
    memcpy(&InstallMsg[install_cnt], &install_msg, sizeof(T_SERVER_INSTALL));


    /**************************************************************************/
    /* 配置接收、发送缓冲区                                                   */
    /**************************************************************************/
    memset(&TcpMsg[install_cnt], 0x00, sizeof(T_TCP_SERVER_MNG));
    
    TcpMsg[install_cnt].pucTcpRecvBuff = (unsigned char *)malloc(TCP_SER_RECV_BUFF_LEN);
    if (NULL == TcpMsg[install_cnt].pucTcpRecvBuff)
    {       
        return (unsigned char)0xfe;
    }   
    
    for(i=0;i<TCP_SER_QUEN_BUFF_LEN;i++)
    {
        TcpMsg[install_cnt].pucTcpSendBuff[i] = (T_TCP_SERVER_MSG *)malloc(sizeof(T_TCP_SERVER_MSG));
        if (NULL == TcpMsg[install_cnt].pucTcpSendBuff[i] )
        {
            return (unsigned char)0xfd;
        }
    }
    
    /**************************************************************************/
    /* 创建TCP服务器端的套接字接口                                            */
    /**************************************************************************/
    
    iSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (SERVER_SOCKET_ERROR == iSocket)
    {
        return (unsigned char)0xfc;
    }
    else
    {
        TcpMsg[install_cnt].iSocket = iSocket;
    }

    /**************************************************************************/
    /* 设置套接字复用属性                                                     */
    /**************************************************************************/
    uiReUse  = 1;
    uiOptLen = sizeof(uiReUse);
    if (SERVER_SOCKET_ERROR == setsockopt(iSocket,
                                   SOL_SOCKET,
                                   SO_REUSEADDR,
                                   (unsigned char *)&uiReUse,
                                   uiOptLen))
    {
        close(iSocket);
        return (unsigned char)0xfb;
    }
    else
    {
    
    }
    /**************************************************************************/
    /* 填写SocketAddr信息                                                     */
    /**************************************************************************/
    memset(&tSocketAddr, 0, sizeof(struct sockaddr_in));

    tSocketAddr.sin_family = AF_INET;
    tSocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    tSocketAddr.sin_port = htons(InstallMsg[install_cnt].PortNum);/* 端口号 */
    
    /**************************************************************************/
    /* 绑定套接字到本地地址                                                   */
    /**************************************************************************/
    if (SERVER_SOCKET_ERROR == bind(iSocket,
                             (struct sockaddr*)&tSocketAddr,
                             sizeof(struct sockaddr)))
    {     
        close(iSocket);
        return (unsigned char)0xfa;
    }
    else
    {

    }
    /**************************************************************************/
    /* 监听服务器端套接字                                                     */
    /**************************************************************************/
    if (SERVER_SOCKET_ERROR == listen(iSocket, SOMAXCONN))
    {    
        close(iSocket);
        return (unsigned char)0xf9;
    }
    else
    {

    }
    install_cnt++; 

    return (unsigned char)0;       
}

// tcp接收任务函数
unsigned char* tcp_server_recv_task()
{
    char revData[TCP_SER_RECV_BUFF_LEN];
    //****开始接收accept()
	struct sockaddr clientAddr;
	int size = sizeof(struct sockaddr);

	int clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, (socklen_t*)&size);
    while(1)
    {

        int ret = recv(clientSock,revData,TCP_SER_RECV_BUFF_LEN, 0);
        if(ret > 0){
            revData[ret] = 0x00;
            cout<<"retrevData:"<<revData<<endl;
        }
    }

}

