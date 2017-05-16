#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <climits>
#include "MemorySharing.hpp"
#include "MemoryPart.hpp"

#define MAX_NUM_TIMES 100
#define MAX_SLEEP_TIME 10
#define NUM_THREADS 100
#define MAX_MEMORY 409600
#define MAX_SIZE 200

std::mutex g_display_mutex;

void print (const int& thread_id, const int *ptr, const int& size) {
    std::lock_guard<std::mutex> lock(g_display_mutex);
    std::cout << "THREAD " << thread_id << " ADDRESS " << std::hex << ptr << " SIZE " << std::dec << size << "\n";
    std::cout << "DATA";
    for (int i = 0; i < size; i++) {
        std::cout << " " << ptr[i];
    }

    std:: cout << std::endl;
}

void libUser(MemorySharing* alloc, const int thread_id) {

    int size = rand() % MAX_SIZE + 1;
    int* ptr = static_cast<int*>(alloc->getMemory(size * sizeof(int)));

    for (int i = 0; i < size; i++) {
        ptr[i] = thread_id;
    }

    int times = rand() % MAX_NUM_TIMES + 1;
    for (int i = 0; i < times; i++) {
        print(thread_id, ptr, size);

        int newSize = rand() % MAX_SIZE + 1;
        ptr = static_cast<int*>(alloc->realloc(ptr, newSize * sizeof(int)));

        for (int i = size; i < newSize; i++) {
            ptr[i] = thread_id;
        }
        size = newSize;

        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % MAX_SLEEP_TIME + 1));
        print(thread_id, ptr, size);
    }
    alloc->freeMemory(ptr);

}


int main(int argc, char const *argv[]) {

    srand (time(NULL));

    MemorySharing* allocator = new MemorySharing();
    allocator->reserveMemory(MAX_MEMORY);

    std::thread threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread(libUser, allocator, i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    // allocator->releaseMemory();

    delete allocator;

    return 0;
}
