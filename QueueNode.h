#ifndef QUEUENODE_H
#define QUEUENODE_H

#include <memory.h>
#include "DoubleCAS.h"

class QueueNode {
  public:
    typedef DPointer<QueueNode,sizeof(size_t)> Pointer;
    int        val;
    Pointer    next;
    QueueNode():next(NULL) {}
    QueueNode(int val) : val(val),next(NULL) {}
};

#endif 