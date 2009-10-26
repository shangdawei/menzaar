/*
 * misc_functions.c
 *
 *  Created on: Sep 7, 2009
 *      Author: kemad
 */
#include <pthread.h>
#include <stdio.h>
#include "datatypes.h"
#include "sla_apis.h"
#include "sla_db.h"


void *signalToggeling( void *toggleInfo )
{
	uint32 i;
	SignalToggleInfo *toggleInfoPtr;
	toggleInfoPtr = (SignalToggleInfo *)toggleInfo;
	for (i=0;i<toggleInfoPtr->numToggles;i++)
	{
		//sleep(toggleInfoPtr->toggleTime);
		slaApiInvertPin(toggleInfoPtr->pinID);
	}
}

void signalDbTogglePin(uint32 pinID,uint32 toggleTime, uint32 numToggles, SignalDb* Db)
{
	/*Init the toggle info passed during thread creation */
	SignalToggleInfo toggleInfo;
	toggleInfo.Db = Db;
	toggleInfo.numToggles = numToggles;
	toggleInfo.pinID = pinID;
	toggleInfo.toggleTime = toggleTime;

	pthread_t thread1;

	int  iret1;

	iret1 = pthread_create( &thread1, NULL, signalToggeling, (void*) &toggleInfo);

	 pthread_join( thread1, NULL);

	 printf("Thread 1 returns: %d\n",iret1);
	 //exit(0);

}

uint32 timeStampTestfn(void)
{
	static int x=-5;
	x+=5;
	return x;
}
