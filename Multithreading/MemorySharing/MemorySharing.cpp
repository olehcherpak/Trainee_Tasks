#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include "MemorySharing.hpp"
#include "MemoryPart.hpp"

MemorySharing::MemorySharing() {
    // partsList = std::list<MemoryPart>();
    memory = nullptr;
}

MemorySharing::~MemorySharing() {
    if (memory != nullptr) {
        delete[] memory;
    }
    partsList.clear();
}

void MemorySharing::reserveMemory(const unsigned size) {
    if (size == 0) {
        throw wrong_size_exception();
    }
    mutex.lock();
    if (memory != nullptr) {
        throw twice_memory_reservation_exception();
    }
    memory = new char[size];
    partsList.push_back(MemoryPart(memory, size));
    mutex.unlock();
}

void* MemorySharing::getMemory(const unsigned& size) {
    if (size == 0) {
        throw wrong_size_exception();
    }
    mutex.lock();
    auto iter = std::find_if(partsList.begin(), partsList.end(), [size] (const MemoryPart& rhs) { return rhs.getLength() >= size && rhs.isFree();});
    if (iter == partsList.end()) {
        throw out_of_memory_exception();
    }

    auto result = cutPart(iter, size);
    mutex.unlock();

    return (void*) result->getPtr();
}

void MemorySharing::freeMemory(void* ptr) {
    auto iter = findPart(ptr);
    mutex.lock();

    iter->makeFree();

    auto next = iter;
    next++;
    combine(iter, next);
    auto prev = iter;
    prev--;
    combine(prev, iter);
    mutex.unlock();
}

void* MemorySharing::realloc(void* ptr, const unsigned& size) {
    auto iter = findPart(ptr);

    if (size <= iter->getLength()) {
        return ptr;
    }
    auto next = iter;
    next++;

    int difference = size - iter->getLength();

    mutex.lock();
    if (next->isFree() && difference <= next->getLength()) {
        auto newPart = cutPart(next, difference);
        combine(iter, newPart);
        mutex.unlock();
        return (void*) iter->getPtr();
    }
    mutex.unlock();

    void* newPtr = getMemory(size);
    void* tmp = ptr;
    mutex.lock();
    copy(ptr, newPtr, iter->getLength());
    mutex.unlock();
    freeMemory(tmp);

    return newPtr;
}

std::list<MemoryPart>::iterator MemorySharing::cutPart(std::list<MemoryPart>::iterator& iter, const unsigned& size) {
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

void MemorySharing::combine(std::list<MemoryPart>::iterator& i, std::list<MemoryPart>::iterator j) {
    if (i->isFree() == j->isFree()) {
        i->setLength(i->getLength() + j->getLength());
        j->makeFree();
        partsList.erase(j);
    }
}

std::list<MemoryPart>::iterator MemorySharing::findPart(void* ptr) {
    auto iter = std::find_if(partsList.begin(), partsList.end(), [ptr] (const MemoryPart& rhs) { return rhs.getPtr() == (char*) ptr;});

    if (iter == partsList.end()) {
        throw bad_pointer_exception();
    }

    return iter;
}

void MemorySharing::copy(void* source, void* target, const unsigned& size) {
    char* src = (char*) source;
    char* trg = (char*) target;

    for (unsigned i = 0; i < size; i++) {
        trg[i] = src[i];
    }
}
