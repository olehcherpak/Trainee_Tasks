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
    mutex->lock();
    auto iter = std::find_if(partsList.begin(), partsList.end(), [size] (const MemoryPart& rhs) { return rhs.getLength() >= size && rhs.free();});
    if (iter == partsList.end()) {
        throw out_of_memory_exception();
    }

    auto result = cutPart(iter, size);
    mutex->unlock();

    return (void*) result->getPtr();
}

void MemorySharing::freeMemory(void* ptr) {
    auto iter = findPart(ptr);
    mutex->lock();

    iter->makeFree();

    auto next = iter;
    next++;
    combine(iter, next);
    auto prev = iter;
    prev--;
    combine(prev, iter);
    mutex->unlock();
}

void* MemorySharing::realloc(void* ptr, const int& size) {
    auto iter = findPart(ptr);

    if (size <= iter->getLength()) {
        return ptr;
    }
    auto next = iter;
    next++;

    int need = size - iter->getLength();

    mutex->lock();
    if (next->free() && need <= next->getLength()) {
        auto newPart = cutPart(next, need);
        combine(iter, newPart);
        mutex->unlock();
        return (void*) iter->getPtr();
    }
    mutex->unlock();

    void* newPtr = getMemory(size);
    void* tmp = ptr;
    mutex->lock();
    copy(ptr, newPtr, iter->getLength());
    mutex->unlock();
    freeMemory(tmp);
    return newPtr;


}

std::list<MemoryPart>::iterator MemorySharing::cutPart(std::list<MemoryPart>::iterator& iter, const int& size) {
    if (iter->getLength() == size) {
        iter->makeBusy();
        return iter;
    }

    char* tmpPtr = iter->getPtr();
    iter->setPtr(tmpPtr + size);
    iter->setLength(iter->getLength() - size);
    MemoryPart tmp = MemoryPart(tmpPtr, size);
    tmp.makeBusy();
    auto res = partsList.insert(iter, tmp);

    return res;
}

void MemorySharing::combine(std::list<MemoryPart>::iterator& iter1, std::list<MemoryPart>::iterator iter2) {
    if (iter1->free() == iter2->free()) {
        iter1->setLength(iter1->getLength() + iter2->getLength());
        iter2->makeFree();
        partsList.erase(iter2);
    }
}

std::list<MemoryPart>::iterator MemorySharing::findPart(void* ptr) {
    auto iter = std::find_if(partsList.begin(), partsList.end(), [ptr] (const MemoryPart& rhs) { return rhs.getPtr() == (char*) ptr;});

    if (iter == partsList.end()) {
        throw bad_pointer_exception();
    }

    return iter;
}

void MemorySharing::copy(void* source, void* target, const int& size) {
    char* src = (char*) source;
    char* trg = (char*) target;

    for (int i = 0; i < size; i++) {
        trg[i] = src[i];
    }
}
