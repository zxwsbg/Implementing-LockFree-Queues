mkdir build
g++ lockfreequeue_test.cpp QueueNode.h LockFreeQueue.h LockFreeQueue.cpp -lpthread -o ./build/lockfreequeue_test
g++ mutexqueue_test.cpp QueueNode.h MutexQueue.h MutexQueue.cpp -lpthread -o ./build/mutexqueue_test
./build/lockfreequeue_test > ./build/1.out
./build/mutexqueue_test > ./build/2.out
python3 check.py 
