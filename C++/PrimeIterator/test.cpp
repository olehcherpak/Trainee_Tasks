#include <iostream>

#include "PrimeIterator.hpp"

int main(int argc, char const *argv[]) {
	for (PrimeIterator iter(8, 10); !iter.over(); iter++) {
		std::cout << *iter << std::endl;
	}

	return 0;
}