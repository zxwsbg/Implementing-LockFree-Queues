cmake_minimum_required(VERSION 3.16)
project(lockfree-queue)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -pthread")

add_executable(lockfree-queue QueueNode.h DoubleCAS.h LockFreeQueue.h LockFreeQueue.cpp lockfreequeue_test.cpp)