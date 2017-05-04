#include <iostream>
#include "Date.hpp"

int main(int argc, char const *argv[]) {
	Date d(4, 5, 2017);
	std::cout << d << std::endl;

	Date d2(-5, 14, -10);
	std::cout << d2 << std::endl;
	return 0;
}