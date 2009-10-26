/*
 * sla_db.h
 *
 *  Created on: Sep 4, 2009
 *      Author: kemad
 */

#ifndef SLA_DB_H_
#define SLA_DB_H_

#define NUM_DB_ELEMENTS_PER_BUFFER 21
#define SWITCH_WATERMARK (NUM_DB_ELEMENTS_PER_BUFFER-1)

/****************Signal DB struct and functions***(Start)*******************/

typedef enum bufferStatus
{
	EMPTY = 0,
	FULL = 1
}BufferStatus;

typedef struct signalDbElement
{
	/*A sequence number for the event order*/
	//uint32 sequenceNo;
	/*Event Time Stamp*/
	uint32 timestamp;
	/*32 bits representing the values of 32 signals*/
	uint32 signal;
}SignalDbElement;

typedef struct signalDb
{
	SignalDbElement signalDbBuff[2][NUM_DB_ELEMENTS_PER_BUFFER];
	SignalDbElement *writeBuff;
	SignalDbElement *readBuff;
	SignalDbElement *prevWrite;
	uint32 currentWriteBuff;
	uint32 writeIndex;
	uint32 readIndex;
	bool   readBufferStatus;
	uint32(*timeStampfnPtr)(void);
}SignalDb;

void signalDbInit(SignalDb *Db, uint32(*timeStampfnPtr)(void));
void signalDbUpdateDb(uint32 mask, SignalDb *Db);
void signalDbDump(SignalDb *Db);

/* There three APIs are moved to sla_apis.h as slaApi...
void signalDbSetPin(uint32 pinID, SignalDb* Db);
void signalDbResetPin(uint32 pinID, SignalDb* Db);
void signalDbInvertPin(uint32 pinID, SignalDb *Db);
*/
//TODO: signalDbDestroy
/****************Signal DB struct and functions***(end)*******************/

typedef struct signalToggleInfo
{
	uint32 pinID;
	uint32 toggleTime;
	uint32 numToggles;
	SignalDb* Db;
}SignalToggleInfo;

void *signalToggeling( void *toggleInfo );
void signalDbTogglePin(uint32 pinID,uint32 toggleTime, uint32 numToggles, SignalDb* Db);
uint32 timeStampTestfn(void);


#endif /* SLA_DB_H_ */
