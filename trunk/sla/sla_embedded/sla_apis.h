/*
 * sla_apis.h
 *
 *  Created on: Sep 10, 2009
 *      Author: kemad
 */

#ifndef SLA_APIS_H_
#define SLA_APIS_H_

/*APIs implemented ocm.c*/
void slaApiStartup(uint32(*timeStampFnPtr)(void));
void slaApiShutdown(void);

/*Apis implemented in sla_db.c*/

void slaApiSetPin(uint32 pinID);
void slaApiResetPin(uint32 pinID);
void slaApiInvertPin(uint32 pinID);

#endif /* SLA_APIS_H_ */
