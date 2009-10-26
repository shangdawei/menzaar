#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "datatypes.h"
#include "sla_db.h"
#include "ocm.h"
#include "connection_handler.h"

void signalDbInit(SignalDb *Db, uint32(*timeStampfnPtr)(void))
{
	/* The following initialization is needed and important however, it is implicitly included
	 * in the memset DB with zero "memset(Db,0,sizeof(*Db))";.
	 * Db->writeIndex = 0;
	 * Db->currentWriteBuff = 0;
	 * To avoid if conditions for the initial prevWrite, it is set to point
	 * at the first element which is zero initialized
	 * memset(Db->signalDbBuff,0,sizeof(Db->signalDbBuff));
	*/
	memset(Db,0,sizeof(*Db));

	Db->writeBuff = &(Db->signalDbBuff[0][0]);
	Db->readBuff = &(Db->signalDbBuff[1][0]);
	Db->prevWrite=&(Db->signalDbBuff[0][0]);
	Db->timeStampfnPtr=timeStampfnPtr;
}

/* This function implements the ping pong buffer used for storing the signal.
 */
void signalDbUpdateDb(uint32 signal, SignalDb *Db)
{
		uint32 *wrtIndx= &(Db->writeIndex);
		SignalDbElement *DbWriteBuff, *DbPrevWrite;
		DbWriteBuff = Db->writeBuff;
		DbPrevWrite = Db->prevWrite;

		//calculate the new mask and place it in the new element
		DbWriteBuff->signal = signal;

		//set sequence number
		//DbWriteBuff->sequenceNo = (DbPrevWrite->sequenceNo) +1;

		//set time stamp
		DbWriteBuff->timestamp = (Db->timeStampfnPtr)();

		//Update previous write buffer
		Db->prevWrite=Db->writeBuff;
		//checking if it is time to switch buffers:
		Db->writeBuff++;
		(*wrtIndx)++;
		//TODO: must be thread safe
		//TODO: check if the current read buffer is dumped or not
		if (SWITCH_WATERMARK == *wrtIndx)
		{
			// If Read buffer is not dumped, dump it
			//TODO: The check is already inside the function,
			//may do another check here for better performance or remove check
			// from inside the function?
			signalDbDump(Db);

			// The write buffer is now full so it will be a read buffer
			Db->readBuff = &(Db->signalDbBuff[Db->currentWriteBuff][0]);
			Db->readBufferStatus = FULL;

			// The new write buffer is the old read one if it is already dumped!!
			Db->currentWriteBuff = !(Db->currentWriteBuff);
			Db->writeBuff=&(Db->signalDbBuff[Db->currentWriteBuff][0]);
			*wrtIndx=0;
		}

}

//This function dumps the read buffer to the GUI application
void signalDbDump(SignalDb *Db)
{
	if (Db->readBufferStatus == FULL)
	{
		chSend((char8*)Db->readBuff,SWITCH_WATERMARK*sizeof(SignalDbElement));
		Db->readBufferStatus = EMPTY;
	}
	else
	{
		printf("Read buffer already dumped!!\n");
	}
}

void slaApiSetPin(uint32 pinID)
{
	SignalDb *Db= &OCM.slaDb;
	//Calculate the mask needed for setting the intended pin
	uint32 signal = (1 << pinID);

	//Calculate the new signal value by oring the mask with the current signal
	signal |= (Db->prevWrite->signal);

	//Update the DB with the new signal
	signalDbUpdateDb(signal,Db);
}

void slaApiResetPin(uint32 pinID)
{
	SignalDb *Db= &OCM.slaDb;
	//Calculate the mask needed for resetting the intended pin
	uint32 signal = ~(1 << pinID);

	//Calculate the new signal value by anding the mask with the current signal
	signal &= (Db->prevWrite->signal);

	//Update the DB with the new signal
	signalDbUpdateDb(signal,Db);
}

void slaApiInvertPin(uint32 pinID)
{
	SignalDb *Db= &OCM.slaDb;
	uint32 signal;
	signal = (1 << pinID);
	signal &= (Db->prevWrite->signal);
	if (signal) slaApiResetPin(pinID);
	else slaApiSetPin(pinID);
}
