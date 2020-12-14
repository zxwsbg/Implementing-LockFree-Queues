g++ lockfreequeue_test.cpp QueueNode.h LockFreeQueue.h LockFreeQueue.cpp -lpthread -o lockfreequeue_test
g++ mutexqueue_test.cpp QueueNode.h MutexQueue.h MutexQueue.cpp -lpthread -o mutexqueue_test
./lockfreequeue_test > 1.out
./mutexqueue_test > 2.out
python3 check.py 
