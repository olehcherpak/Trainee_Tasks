#include "CustomVector.hpp"
#include <climits>
#define DEFAULT_CAPACITY 1
#define CAPACITY_MULTIPLIER 2

CustomVector::CustomVector(const unsigned n) {
    curCapacity = n;
    curSize = 0;
    dataArray = new int[curCapacity];
}

CustomVector::CustomVector() {
    curCapacity = DEFAULT_CAPACITY;
    curSize = 0;
    dataArray = new int[DEFAULT_CAPACITY];
}

CustomVector::CustomVector(const unsigned n, const int& val) {
    curCapacity = n;
    dataArray = new int[curCapacity];
    for (curSize = 0; curSize < curCapacity; curSize++) {
        dataArray[curSize] = val;
    }
}

CustomVector::~CustomVector() {
    delete dataArray;
}

CustomVector& CustomVector::operator=(const CustomVector& x) {
    this->clear();
    this->curSize = x.curSize;
    this->reserve(x.curSize);
    this->copyHandler(x.dataArray, this->dataArray);
    return *this;
}

unsigned CustomVector::size() const {
    return curSize;
}

unsigned CustomVector::max_size() const {
    return UINT_MAX;
}

void CustomVector::resize(unsigned newSize, int val) {
    if (newSize < curSize) {
        curSize = newSize;
        resizeHandler();
        return;
    }
    if (newSize > curCapacity) {
        reserve(newSize);
    }

    for (unsigned i = curSize; i < newSize; i++) {
        dataArray[i] = val;
    }
    curSize = newSize;
}

unsigned CustomVector::capacity() const {
    return curCapacity;
}

bool CustomVector::empty() const {
    return curSize == 0;
}

void CustomVector::reserve(unsigned size) {
    if (curCapacity < size) {
        int* newArray = new int[size];
        curCapacity = size;
        copyHandler(dataArray, newArray);
        delete dataArray;
        dataArray = newArray;
    }
}

int& CustomVector::operator[] (unsigned index) {
    return dataArray[index];
}

const int& CustomVector::operator[] (unsigned index) const {
    return dataArray[index];
}

int& CustomVector::at(unsigned index) {
    if (index >= curSize) {
        throw out_of_range();
    }

    return dataArray[index];
}
int& CustomVector::front() {
    return *dataArray;
}

const int& CustomVector::front() const {
    return *dataArray;
}

int& CustomVector::back() {
    return dataArray[curSize - 1];
}

const int& CustomVector::back() const {
    return dataArray[curSize - 1];
}

void CustomVector::assign(unsigned newSize, const int& val) {
    if (curCapacity < newSize) {
        int* newArray = new int[newSize];
        curCapacity = newSize;
        delete dataArray;
        dataArray = newArray;
    }
    reserve(newSize);
    for (unsigned i = 0; i < newSize; i++) {
        dataArray[i] = val;
    }
    curSize = newSize;
}

void CustomVector::push_back(const int& val) {
    if (curSize == curCapacity) {
        reserve(curCapacity * CAPACITY_MULTIPLIER);
    }
    dataArray[curSize] = val;
    curSize += 1;
}

void CustomVector::pop_back() {
    curSize -= 1;
}

void CustomVector::insert(unsigned position, const int& val) {
    moveHandler(position, 1);
    dataArray[position] = val;
}

void CustomVector::insert(unsigned position, unsigned newSize, const int& val) {
    moveHandler(position, newSize);
    unsigned finish = position + newSize;
    for(unsigned i = position; i < finish; i++) {
        dataArray[i] = val;
    }
}

void CustomVector::erase(unsigned position) {
    erase(position, position + 1);
}

void CustomVector::erase(unsigned start, unsigned finish) {
    unsigned length = finish - start;
    curSize -= length;
    for (unsigned i = start, j = start + length; i < curSize; i++, j++) {
        dataArray[i] = dataArray[j];
    }
}

void CustomVector::swap(CustomVector& x) {
    unsigned tmpSize = curSize;
    unsigned tmpCapacity = curCapacity;
    int* tmpData = dataArray;

    curSize = x.size();
    curCapacity = x.capacity();
    dataArray = x.dataArray;

    x.curSize = tmpSize;
    x.curCapacity = tmpCapacity;
    x.dataArray = tmpData;
}

void CustomVector::clear() {
    curSize = 0;
}

void CustomVector::copyHandler(int* source, int* target) {
    for (unsigned i = 0; i < curSize; i++) {
        target[i] = source[i];
    }
}

void CustomVector::moveHandler(unsigned start, unsigned length = 1) {
    resize(curSize + length);
    unsigned cache = start + length;
    for (unsigned i = curSize, j = curSize - length; i > cache; i--, j--) {
        dataArray[i] = dataArray[j];
    }
}

void CustomVector::resizeHandler() {
    int* newArray = new int[curSize];
    curCapacity = curSize;
    copyHandler(dataArray, newArray);
    delete dataArray;
    dataArray = newArray;
}
