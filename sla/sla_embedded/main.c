/*
 * main.c
 *
 *  Created on: Sep 7, 2009
 *      Author: kemad
 */
#include <stdio.h>
#include "datatypes.h"
#include "sla_apis.h"
#include "sla_db.h"
#include "connection_handler.h"
#include "ocm.h"

int main(void)
{
	Ocm *ocmPtr=&OCM;
	int i;
	slaApiStartup(timeStampTestfn);
	printf("start\n");
/*
	for (i=0;i<5;i++)
		{
		slaApiSetPin(i);
		}
*/
	slaApiResetPin(0);
	for (i=0;i<19;i++)
	{
		slaApiInvertPin(0);
	}
	slaApiResetPin(0);
		for (i=0;i<10;i++)
		{
			slaApiInvertPin(1);
		}
	signalDbDump(& OCM.slaDb);
	//signalDbTogglePin(1,1,1,&testDb);
	/*
	for (i=0;i<5;i++)
		{
			signalDbInvertPin(i,&testDb);
		}
	*/
	printf("end\n");

	return 0;
}
