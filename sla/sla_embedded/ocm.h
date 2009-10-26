/*
 * ocm.h
 *
 *  Created on: Sep 9, 2009
 *      Author: kemad
 */

#ifndef OCM_H_
#define OCM_H_

typedef enum slaStatus
{
	SLA_DOWN = 0,
	SLA_UP = 1
} SlaStatus;

typedef struct ocm
{
	SlaStatus status;
	SignalDb slaDb;
}Ocm;

extern Ocm OCM;
#endif /* OCM_H_ */
