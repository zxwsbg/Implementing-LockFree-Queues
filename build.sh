g++ lockfreequeue_test.cpp LockFreeQueue.h LockFreeQueue.cpp -lpthread -o lockfreequeue_test
# g++ mutex_test.cpp -lpthread -o mutex_test
./lockfreequeue_test > 1.out
python3 check.py < 1.out 