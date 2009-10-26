/*
 * connection_handler.c
 *
 *  Created on: Sep 7, 2009
 *      Author: kemad
 */
#include "stdio.h"
#include "tcp_client.h"
#include "connection_handler.h"

static Connection slaConnection;


void chConnect(ConnectionType type)
{
	switch (type)
	{
	case TCP:
		slaConnection.type = TCP;
		tcpConnect();
		break;
	default:
		printf("Error in type");
	}
}

void chSend (char *buffer, unsigned int length)
{
	switch (slaConnection.type)
	{
	case TCP:
		tcpSend ((char*)(&length),4);
		tcpSend (buffer,length);
		break;
	default:
		printf("Error in type");
	}
}

/*Note: No need for length here as the first 4 bytes will always contain the length
 *We will always receive first 4 bytes first to get the length then call receive again
 *With the received length */
void chReceive (char *buffer)
{
	switch (slaConnection.type)
	{
	case TCP:
		tcpRecv (buffer);

		break;
	default:
		printf("Error in type");
	}
}

//TODO: remove this extra level and call send directly from the switch case in chSend
void tcpSend (char *sendBuffer, unsigned int length)
{
	send(slaConnection.connectionId,sendBuffer,length,0);
}

void tcpRecv(char *recvBuffer)
{
	int length;
	recv(slaConnection.connectionId,(char*)length,LENGTH_HEADER_SIZE,0);
	recv(slaConnection.connectionId,recvBuffer,length,0);
}
void tcpConnect(void)
{
	slaConnection.connectionId=tcpClientConnectToServer("172.25.25.193",4444);
}



