#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queues.h"

extern int currentPID;

extern CircularQueue * runningQueue;
extern CircularQueue * blockedQueue;
extern Proc * p0;

void initScheduler();
Proc * next();
void proc0();

#endif