#include <iostream>
#include <thread>
#include <vector>
#include "LockFreeQueue.h"

int            thread_number;
int            task_number; // 每个线程需要入队/出队的资源个数
int            total_number;
LockFreeQueue* lfq;

void produce(int offset)
{
    // 算上偏移量，保证不会出现重复
    for (int i = task_number * offset; i < task_number * (offset + 1); i++) { 
        lfq->enqueue(i);
        printf("produce %d\n", i);
    }
}

void consume()
{
    while(total_number > 0) {
        int res = lfq->dequeue();
        if (res >= 0) {
            printf("consume %d\n", res);
            __sync_fetch_and_sub(&total_number, 1);
            printf("total : %d\n", total_number);
        }
        else
            printf("Fail to consume!\n");
    }
}

int main(int argc, char** argv)
{
    lfq = new LockFreeQueue;
    std::vector<std::thread> thread_vector1;
    std::vector<std::thread> thread_vector2;

    if (argc < 3) {
        thread_number = 10;
        task_number   = 100000;
    }
    else {
        thread_number = atoi(argv[1]);
        task_number   = atoi(argv[2]);
    }
    total_number = task_number*thread_number;

    for (int i = 0; i < thread_number; i++) {
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
