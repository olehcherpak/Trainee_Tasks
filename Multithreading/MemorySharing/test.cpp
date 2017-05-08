#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <climits>
#include "MemorySharing.hpp"
#include "MemoryPart.hpp"

#define MAX_NUM_TIMES 10
#define MAX_SLEEP_TIME 10
#define NUM_THREADS 20
#define MAX_MEMORY 4096

std::mutex g_display_mutex;

void print (const int& thread_id, const int *ptr, const int& size) {
    g_display_mutex.lock();

    std::cout << "THREAD " << thread_id << " ADDRESS " << std::hex << ptr << " SIZE " << std::dec << size << "\n";
    std::cout << "DATA";
    for (int i = 0; i < size; i++) {
        std::cout << " " << ptr[i];
    }
    std:: cout << std::endl;

    g_display_mutex.unlock();
}

void workingFunction(MemorySharing* alloc, const int thread_id) {

    int size = rand() % 20 + 1;
    int* ptr = (int*) alloc->getMemory(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        ptr[i] = thread_id;
    }

    int times = rand() % MAX_NUM_TIMES + 1;
    for (int i = 0; i < times; i++) {
        print(thread_id, ptr, size);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % MAX_SLEEP_TIME + 1));
        print(thread_id, ptr, size);
    }

}


int main(int argc, char const *argv[]) {

    srand (time(NULL));

    MemorySharing* allocator = new MemorySharing();
    allocator->reserveMemory(MAX_MEMORY);

    std::thread t[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        t[i] = std::thread(workingFunction, allocator, i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        t[i].join();
    }

    allocator->releaseMemory();

    delete allocator;

    return 0;
}
