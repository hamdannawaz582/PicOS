#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queues.h"

extern QueueEntry * currentProc;
extern QueueEntry * nextProc;

extern CircularQueue * readyQueue;
extern CircularQueue * runningQueue;
extern CircularQueue * blockedQueue;

void initScheduler();

#endif