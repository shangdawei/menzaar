/*
 * ocm.c
 *
 *  Created on: Sep 9, 2009
 *      Author: kemad
 */
#include "datatypes.h"
#include "sla_db.h"
#include "connection_handler.h"
#include "sla_apis.h"
#include "ocm.h"

 Ocm OCM;

void slaApiStartup(uint32(*timeStampFnPtr)(void))

{
		OCM.status=SLA_DOWN;
		signalDbInit(& OCM.slaDb,timeStampFnPtr);
		chConnect(TCP);
		OCM.status=SLA_UP;
}
