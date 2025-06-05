#ifndef QUEUES_H
#define QUEUES_H

// Ready Queue ought to be a circular queue :pepethink:
#include "proc.h"

typedef struct QueueEntry {
    Proc * process;
    struct QueueEntry * next;
} QueueEntry;

typedef struct CircularQueue {
    QueueEntry * head;
    QueueEntry * tail;
} CircularQueue;

void addProcToQueue(struct Proc * process, struct CircularQueue * queue);
void removeProcFromQueue(struct Proc * process, struct CircularQueue * queue);
Proc * popHead(struct CircularQueue * queue);

#endif