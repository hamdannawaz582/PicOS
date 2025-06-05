#include "queues.h"
#include "pico/stdlib.h"
#include "malloc.h"

void prepareQueues() {
    
}

void addProcToQueue(Proc *process, CircularQueue *queue) {
    if (queue->head == NULL) {
        queue->head = queue->tail = malloc(sizeof(QueueEntry));
    } else {
        queue->tail->next = malloc(sizeof(QueueEntry));
        queue->tail = queue->tail->next;
    }
    queue->tail->process = process;
    queue->tail->next = NULL;
}

void removeProcFromQueue(Proc *process, CircularQueue *queue) {

}

Proc * popHead(CircularQueue *queue) {
    if (queue->head == NULL) return NULL;
    QueueEntry * ret = queue->head;
    queue->head = ret->next;
    Proc * retval = ret->process;
    free(ret);
    return retval;
}