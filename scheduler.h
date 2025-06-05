#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queues.h"

extern Proc * current;

extern CircularQueue * runningQueue;
extern CircularQueue * blockedQueue;
extern Proc * p0;

void initScheduler();
Proc * next();
void add(Proc *);
void proc0();

#endif