/*
 * tcp_client.c
 *
 *  Created on: Sep 7, 2009
 *      Author: kemad
 */

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp_client.h"

#if 0
int main (void)
{

	int SocketId;
	SocketId=tcpClientConnectToServer("192.168.1.5",4444);
	{
		char buff[1000]="FromClient";
		int length=1000;
		send(SocketId,buff,11,0);
		//printf("\n%s\n",buff);
		recv(SocketId,buff,11,0);
		printf("\n%s\n",buff);
		shutdown(SocketId,2);
		close(SocketId);
	}
	return 0;

}
#endif

int tcpClientConnectToServer (char * serverIpAddress, short portNumber)
{
	struct sockaddr_in serverAddr,*serverAddrPtr;
		int socketId;
		serverAddrPtr = & serverAddr;
		memset(serverAddrPtr,0,sizeof(*serverAddrPtr));
		socketId = socket(AF_INET,SOCK_STREAM,0);
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr  = inet_addr("172.25.25.193");
		serverAddr.sin_port = htons(4444);
		connect(socketId,(struct sockaddr*)serverAddrPtr,sizeof(serverAddr));
		return socketId;
}
