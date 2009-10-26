/*
 * connection_handler.h
 *
 *  Created on: Sep 7, 2009
 *      Author: kemad
 */

#ifndef CONNECTION_HANDLER_H_
#define CONNECTION_HANDLER_H_

#define LENGTH_HEADER_SIZE 4

typedef enum connectionType
{
	TCP = 1,
	SERIAL = 2,
	USB = 3
}ConnectionType;

typedef struct connection
{
	int connectionId;
	ConnectionType type;
}Connection;

void chConnect(ConnectionType type);
void chSend (char *buffer, unsigned int length);
void chReceive (char *buffer);

void tcpConnect(void);
void tcpSend (char *sendBuffer, unsigned int length);
void tcpRecv(char *recvBuffer);

#endif /* CONNECTION_HANDLER_H_ */
