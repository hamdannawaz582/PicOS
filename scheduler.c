#include "scheduler.h"

QueueEntry * currentProc = NULL;
QueueEntry * nextProc = NULL;
CircularQueue * readyQueue = NULL;
CircularQueue * runningQueue = NULL;
CircularQueue * blockedQueue = NULL;

void initScheduler() {

}