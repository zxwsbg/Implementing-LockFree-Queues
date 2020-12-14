#include "MutexQueue.h"

#include <thread>
#include <vector>

int         thread_number;
int         task_number;
MutexQueue* lfq;

void produce(int offset)
{
    for (int i = task_number * offset; i < task_number * (offset + 1); i++) {
        printf("produce %d\n", i);
        lfq->enqueue(i);
    }
}

void consume()
{
    for (int i = 0; i < task_number; i++) {
        int res = lfq->dequeue();
        if (res > 0)
            printf("consume %d\n", res);
        else
            printf("Fail to consume!\n");
    }
}

int main(int argc, char** argv)
{
    lfq = new MutexQueue;
    std::vector<std::thread> thread_vector1;
    std::vector<std::thread> thread_vector2;

    if (argc < 3) {
        thread_number = 10;
        task_number = 10000;
    }
    else {
        thread_number = atoi(argv[1]);
        task_number = atoi(argv[2]);
    }

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