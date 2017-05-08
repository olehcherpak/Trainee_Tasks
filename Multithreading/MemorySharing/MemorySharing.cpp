#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include "MemorySharing.hpp"
#include "MemoryPart.hpp"

MemorySharing::MemorySharing() {
    partsList = std::list<MemoryPart>();
    memory = nullptr;
    mutex = new std::mutex;
}

MemorySharing::~MemorySharing() {
    delete mutex;
}

void MemorySharing::reserveMemory(const int& size) {
    if (size <= 0) {
        throw wrong_size_exception();
    }
    mutex->lock();
    memory = new char[size];
    partsList.push_back(MemoryPart(memory, size));
    mutex->unlock();
}

void MemorySharing::releaseMemory() {
    mutex->lock();
    for (auto iter = partsList.begin(); iter != partsList.end(); iter++) {
        if (!iter->free()) {
            iter->makeFree();
        }
    }
    if (memory != nullptr) {
        delete[] memory;
        memory = nullptr;
    }
    partsList.clear();
    mutex->unlock();
}

void* MemorySharing::getMemory(const int& size) {
    if (size <= 0) {
        throw wrong_size_exception();
    }
    auto iter = std::find_if(partsList.begin(), partsList.end(), [size] (const MemoryPart& rhs) { return rhs.getLength() >= size && rhs.free();});
    if (iter == partsList.end()) {
        throw out_of_memory_exception();
    }
    mutex->lock();
    void* result = cutPart(iter, size);
    mutex->unlock();

    return result;
}

void MemorySharing::freeMemory(void* ptr) {
    auto iter = std::find_if(partsList.begin(), partsList.end(), [ptr] (const MemoryPart& rhs) { return rhs.getPtr() == ptr;});
    if (iter == partsList.end()) {
        throw bad_pointer_exception();
    }
    iter->makeFree();
    mutex->lock();
    combine(iter);
    mutex->unlock();
}

void* MemorySharing::cutPart(std::list<MemoryPart>::iterator& iter, const int& size) {
    char* tmpPtr = iter->getPtr();
    iter->setPtr(tmpPtr + size);
    iter->setLength(iter->getLength() - size);
    MemoryPart tmp = MemoryPart(tmpPtr, size);
    tmp.makeBusy();
    partsList.insert(iter, tmp);

    return (void*)(tmpPtr);
}

void MemorySharing::combine(std::list<MemoryPart>::iterator& partIterator) {
    auto tmpIter = partIterator;
    partIterator++;
    if (tmpIter->free() && partIterator->free()) {
        tmpIter->setLength(tmpIter->getLength() + partIterator->getLength());
        partsList.erase(partIterator);
    }

    partIterator = tmpIter;
    partIterator--;
    if (tmpIter->free() && partIterator->free()) {
        partIterator->setLength(partIterator->getLength() + tmpIter->getLength());
        partsList.erase(tmpIter);
    }
}
