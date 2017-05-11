#include <mutex>

#include "MemoryPart.hpp"

MemoryPart::MemoryPart(char* start, const int& size) : startPtr(start), length(size), status(true) {

}

MemoryPart::~MemoryPart() {

}

bool MemoryPart::free() const {
    return status;

}

void MemoryPart::makeBusy() {
    mutex = new std::mutex;
    mutex->lock();
    status = false;
}

void MemoryPart::makeFree() {
    if (status) {
        return;
    }
    status = true;
    mutex->unlock();
    delete mutex;
}

int MemoryPart::getLength() const {
    return length;
}

void MemoryPart::setLength(const int& newLength) {
    length = newLength;
}

char* MemoryPart::getPtr() const {
    return startPtr;
}

void MemoryPart::setPtr(char* newPtr) {
    startPtr = newPtr;
}
