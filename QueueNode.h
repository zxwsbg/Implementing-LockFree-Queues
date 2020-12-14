#ifndef QUEUENODE_H
#define QUEUENODE_H

#include <memory.h>

class QueueNode {
  public:
    int        val;
    QueueNode* next;
    QueueNode(int val) : val(val) {
        next = NULL;
    }
};

#endif 