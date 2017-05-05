#include <climits>
#include <cmath>
#include "PrimeIterator.hpp"

PrimeIterator::PrimeIterator(const int& first, const int& limit):start(first), finish(first + limit) {
	if (first == 0) {
		throw unvalid_data_exception();
	}
	for (numberValue = 3, index = 1; index != start; numberValue++) {
		for (int j=2; j <= numberValue; j++) {
            if (numberValue % j == 0) {
                break;
            } else if (j+1 > sqrt(numberValue)) {
                index++;
                break;
            }
        }
	}
	numberValue -= 1;
}

PrimeIterator::~PrimeIterator() {

}

int PrimeIterator::getIndex() const {
	return index;
}

void PrimeIterator::next() {
	for (int i = numberValue + 1; i < INT_MAX; i++) {
        for (int j=2; j <= i; j++) {
            if (i % j == 0) {
                break;
            } else if (j + 1 > sqrt(i)) {
                index += 1;
                numberValue = i;
                return;
            }
        }
    }
}

void PrimeIterator::prev() {
	for (int i = numberValue-1; i > 0; i--) {
        for (int j = 2; j <= i; j++) {
            if (i % j == 0) {
                break;
            } else if (j + 1 > sqrt(i)) {
                index -= 1;
                numberValue = i;
                return;
            }
        }
    }
}

int PrimeIterator::value() {
	return numberValue;
}

bool PrimeIterator::over() const {
	return index == finish;
}

bool PrimeIterator::first() const {
	return index == start;
}

int PrimeIterator::operator++() {
	int res = numberValue;
	next();
	return res;
}

int PrimeIterator::operator++(int) {
	next();
	return numberValue;
}

int PrimeIterator::operator--() {
	int res = numberValue;
	prev();
	return res;
}

int PrimeIterator::operator--(int) {
	prev();
	return numberValue;
}

int PrimeIterator::operator*() {
	return numberValue;
}
