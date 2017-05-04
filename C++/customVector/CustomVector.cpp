#include "CustomVector.hpp"

#define DEFAULT_CAPACITY 256
#define CAPACITY_MULTIPLIER 2

CustomVector::CustomVector(unsigned n) {
	curCapacity = n;
	curSize = 0;
	dataArray = new int[curCapacity];
}

CustomVector::CustomVector() {
	curCapacity = DEFAULT_CAPACITY;
	curSize = 0;
	dataArray = new int[DEFAULT_CAPACITY];
}

CustomVector::CustomVector(const unsigned n, int val) {
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
	return ~0;
}

void CustomVector::resize(unsigned n, int val) {
	if (n < curSize) {
		curSize = n;
	} else {
		if (n > curCapacity) {
			reserve(curCapacity + n);
		}
		for (; curSize < n; curSize++) {
			dataArray[curSize] = val;
		}
	}
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

int& CustomVector::operator[] (unsigned n) {
	return dataArray[n];
}

const int& CustomVector::operator[] (unsigned n) const {
	return dataArray[n];
}

int& CustomVector::at(unsigned index) {
	if (index >= curSize) {
		throw out_of_range();
	} else {
		return dataArray[index];
	}
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

void CustomVector::assign (unsigned n, const int& val) {
	if (curCapacity < n) {
		int* newArray = new int[n];
		curCapacity = n;
		delete dataArray;
		dataArray = newArray;
	}
	for (curSize = 0; curSize < n; curSize++) {
		dataArray[curSize] = val;
	}
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

void CustomVector::insert(unsigned position, unsigned n, const int& val) {
	moveHandler(position, n);
	for(unsigned i = position; i < position + n; i++) {
		dataArray[i] = val;
	}
}

void CustomVector::erase(unsigned position) {
	erase(position, position + 1);
}

void CustomVector::erase(unsigned start, unsigned finish) {
	unsigned cache = finish - start;
	curSize -= cache;
	for (unsigned index = start; index < curSize; index++) {
		dataArray[index] = dataArray[index + cache];
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
	int limit;
	if (curSize < curCapacity) {
		limit = curSize;
	} else {
		limit = curCapacity;
	}
	for (int index = 0; index < limit; ++index) {
		target[index] = source[index];
	}
}

void CustomVector::moveHandler(unsigned start, unsigned n = 1) {
	resize(curSize + n);
	unsigned cache = start + n;
	for (unsigned position = curSize; position > cache; position--) {
		dataArray[position] = dataArray[position - n];
	}
}
