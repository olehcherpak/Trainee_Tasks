#include <mutex>

#include "MemoryPart.hpp"
#include "MemorySharing.hpp"

MemoryPart::MemoryPart(char* start, const unsigned& size) : startPtr(start), length(size), status(true) {}

MemoryPart::~MemoryPart() {}

bool MemoryPart::isFree() const {
    return status;
}

void MemoryPart::makeBusy() {
    status = false;
}

void MemoryPart::makeFree() {
    if (status) {
        return;
    }
    status = true;
}

unsigned MemoryPart::getLength() const {
    return length;
}

void MemoryPart::setLength(const unsigned& newLength) {
    length = newLength;
}

char* MemoryPart::getPtr() const {
    return startPtr;
}

void MemoryPart::setPtr(char* newPtr) {
    if (newPtr == nullptr) {
        throw bad_pointer_exception();
    }
    startPtr = newPtr;
}
