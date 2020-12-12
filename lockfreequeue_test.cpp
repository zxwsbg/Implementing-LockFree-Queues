#include <iostream>
#include <thread>
#include <vector>
#include "LockFreeQueue.h"

int thread_number;
LockFreeQueue* lfq;

void produce(int offset)
{
    for (int i = 20 * offset; i < 20 * (offset + 1); i++) {
        printf("produce %d\n", i);
        lfq->enqueue(i);
    }
}

void consume()
{
    for (int i = 0; i < 20; i++) {
        int res = lfq->dequeue();
        if (res > 0)
            printf("consume %d\n", res);
        else
            printf("Fail to consume!\n");
    }
}

int main(int argc, char** argv)
{
    lfq = new LockFreeQueue;
    std::vector<std::thread> thread_vector1;
    std::vector<std::thread> thread_vector2;

    if(argc < 2) {
        thread_number = 10;
    } else {
        thread_number = atoi(argv[1]);
    }

    for (int i = 0; i != 5; ++i) {
        thread_vector1.push_back(std::thread(produce, i));
        thread_vector2.push_back(std::thread(consume));
    }

    for (auto& thr1 : thread_vector1) {
        thr1.join();
    }

    for (auto& thr2 : thread_vector2) {
        thr2.join();
    }
    return 0;
}
