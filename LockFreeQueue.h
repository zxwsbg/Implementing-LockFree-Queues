#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H

#include "QueueNode.h"

class LockFreeQueue {
  public:
    typedef DPointer<QueueNode,sizeof(size_t)> Pointer;
    LockFreeQueue();
    bool enqueue(int val);
    int  dequeue();
    int  encode(int val); // int的前24位存放原值，后8位存放引用计数
    int  decode(int val);
    ~LockFreeQueue();

  private:
    int        queue_size; // 暂时未使用，论文里并没有提及最大资源数
    Pointer    Head, Tail;
};


#endif  // LOCKFREEQUEUE_H
