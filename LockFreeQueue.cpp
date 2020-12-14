#include "LockFreeQueue.h"

LockFreeQueue::LockFreeQueue()
{
    head = new QueueNode(-1);
    tail = head;
}

LockFreeQueue::~LockFreeQueue() {}

bool LockFreeQueue::enqueue(int val)
{
    QueueNode* cur_node;
    QueueNode* add_node = new QueueNode(val);
    while (1) {
        cur_node = tail;
        if (__sync_bool_compare_and_swap(&(cur_node->next), NULL, add_node)) {
            break;
        }
        else {
            __sync_bool_compare_and_swap(&tail, cur_node, cur_node->next);
        }
    }
    __sync_bool_compare_and_swap(&tail, cur_node, add_node);
    return 1;
}

int LockFreeQueue::dequeue()
{
    QueueNode* cur_node;
    int        val;
    while (1) {
        cur_node = head;
        if (cur_node->next == NULL) {
            return -1;
        }

        if (__sync_bool_compare_and_swap(&head, cur_node, cur_node->next)) {
            break;
        }
    }
    val = cur_node->next->val;
    delete cur_node;
    return val;
}