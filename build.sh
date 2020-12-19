rm -rf build
mkdir build
g++ lockfreequeue_test.cpp DoubleCAS.h QueueNode.h LockFreeQueue.h LockFreeQueue.cpp -lpthread -o ./build/lockfreequeue_test
./build/lockfreequeue_test > ./build/1.out
python3 check.py 
