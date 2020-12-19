#include "LockFreeQueue.h"

LockFreeQueue::LockFreeQueue()
{
    QueueNode* node = new QueueNode();
    Head.ptr = Tail.ptr = node;
}

LockFreeQueue::~LockFreeQueue() {}

bool LockFreeQueue::enqueue(int val)
{
    QueueNode* cur_node = new QueueNode(val);
    Pointer    tail, next;

    do {
        tail = Tail;
        next = tail.ptr->next;
        if (tail == Tail) {
            if (next.ptr == NULL) {
                if (tail.ptr->next.double_cas(Pointer(cur_node, next.count + 1), next))
                    break;
            }
            else {
                Tail.double_cas(Pointer(next.ptr, tail.count + 1), tail);
            }
        }
    } while (true);
    Tail.double_cas(Pointer(cur_node, tail.count + 1), tail);
}

int LockFreeQueue::dequeue()
{
    int ret = -1;
    Pointer head, tail, next;
    do {
        head = Head;
        tail = Tail;
        next = head.ptr->next;
        if (head == Head)
            if (head.ptr == tail.ptr) {
                if (next.ptr == NULL)
                    return ret;
                Tail.double_cas(Pointer(next.ptr, tail.count + 1), tail);
            }
            else {
                ret = next.ptr->val;
                if (Head.double_cas(Pointer(next.ptr, head.count + 1), head))
                    break;
            }
    } while (true);
    delete (head.ptr);
    return ret;
}