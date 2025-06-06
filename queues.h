/* queues.h - addProcToQueue, removeProcFromQueue, popHead */
#ifndef QUEUES_H
#define QUEUES_H

#include "proc.h"
#include "pico/stdlib.h"
#include "malloc.h"

typedef struct QueueEntry {
    Proc * process;
    struct QueueEntry * next;
} QueueEntry;

typedef struct CircularQueue {
    QueueEntry * head;
    QueueEntry * tail;
} CircularQueue;

/*----------------------------------------------------------------------
 * addProcToQueue - adds a process to given queue                       
 * Input:
 *  process     -   Pointer to process to add
 *  queue       -   Pointer to the addee queue
 *                                                                
 * Output:
 *                                                               
 ----------------------------------------------------------------------*/
void addProcToQueue(Proc *process, CircularQueue *queue) {
    if (queue->head == NULL) {
        queue->head = queue->tail = malloc(sizeof(QueueEntry)); // Allocate memory enough for a QueueEntry
    } else {
        queue->tail->next = malloc(sizeof(QueueEntry));
        queue->tail = queue->tail->next;
    }
    // Add process to tail
    queue->tail->process = process;
    queue->tail->next = NULL;
}

/*----------------------------------------------------------------------
 * removeProcFromQueue - removes a process from a given queue                       
 * Input:
 *  PID         -   PID of process to remove
 *  queue       -   Pointer to the queue to remove from
 *                                                                
 * Output:
 *  Proc *      -   Pointer to the process removed                                                               
 ----------------------------------------------------------------------*/
Proc * removeProcFromQueue(int PID, CircularQueue *queue) {
    return NULL;
}

/*----------------------------------------------------------------------
 * popHead - removes first process from a given queue                       
 * Input:
 *  queue       -   Pointer to the queue to remove from
 *                                                                
 * Output:
 *  Proc *      -   Pointer to the process removed                                                               
 ----------------------------------------------------------------------*/
Proc * popHead(CircularQueue *queue) {
    if (queue->head == NULL) return NULL;
    QueueEntry * ret = queue->head;
    queue->head = ret->next;
    Proc * retval = ret->process;
    free(ret);
    return retval;
}

#endif