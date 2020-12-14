#include "MutexQueue.h"

MutexQueue::MutexQueue()
{
    head = new QueueNode(-1);
    tail = head;
}

MutexQueue::~MutexQueue() {}

bool MutexQueue::enqueue(int val)
{
    QueueNode* add_node = new QueueNode(val);
    std::unique_lock<std::mutex> lck(mtx);

    while (queue_size == max_size) {
        printf("Slot Full!\n");
        not_full.wait(lck);
    }
    tail->next          = add_node;
    tail                = add_node;
    queue_size++;
    not_empty.notify_all();
    lck.unlock();
    return 1;
}

int MutexQueue::dequeue()
{
    int val;
    std::unique_lock<std::mutex> lck(mtx);
    
    while (queue_size == 0) {
        printf("Slot empty!\n");
        not_empty.wait(lck); 
    }
    queue_size--;
    val = head->next->val;
    head = head->next;
    not_full.notify_all();
    lck.unlock();
    return val;
}