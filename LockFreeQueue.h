#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

class QueueNode {
  public:
    int        val;
    QueueNode* next;
    QueueNode(int val) : val(val) {
        next = NULL;
    }
};

class LockFreeQueue {
  public:
    LockFreeQueue();
    bool enqueue(int val);
    int  dequeue();
    ~LockFreeQueue();

  private:
    int        queue_size;
    QueueNode* tail;
    QueueNode* head;
};

#endif  // LOCKFREEQUEUE_H
