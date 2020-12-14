#ifndef MUTEXQUEUE_H
#define MUTEXQUEUE_H

#include "QueueNode.h"
#include <mutex>
#include <condition_variable>

class MutexQueue {
  public:
    MutexQueue();
    bool enqueue(int val);
    int  dequeue();
    ~MutexQueue();

  private:
    int        max_size = 100000;
    int        queue_size;
    QueueNode* tail;
    QueueNode* head;
    std::mutex mtx;
    std::mutex producer_count_mtx;
    std::mutex consumer_count_mtx;

    std::condition_variable not_full;
    std::condition_variable not_empty;
};

#endif  // MUTEXQUEUE_H
