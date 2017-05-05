#include <iostream>
#include "CustomVector.hpp"

int main(int argc, char const *argv[])
{
	CustomVector vec(5, 10);
	vec.push_back(8);
	vec.clear();
	std::cout << vec.empty() << std::endl;	
	
	CustomVector foo (3,0);
  	CustomVector bar (5,0);

  	bar = foo;
  	foo = CustomVector();

  	std::cout << "Size of foo: " << foo.size() << '\n';
  	std::cout << "Size of bar: " << bar.size() << '\n';

  	CustomVector myvector;

	for (int i=1;i<10;i++) {
		myvector.push_back(i);
	}

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	unsigned size = myvector.size();
	for (unsigned i = 0;i < size; i++) {
		std::cout << ' ' << myvector[i];
	}
	std::cout << '\n';

	std::cout << "size: " << myvector.size() << '\n';
  	std::cout << "capacity: " << myvector.capacity() << '\n';
  	std::cout << "max_size: " << myvector.max_size() << '\n';

  	foo = CustomVector(3, 100);
  	bar = CustomVector(5, 200);
  	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++) {
		std::cout << ' ' << foo[i];
	}
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++) {
		std::cout << ' ' << bar[i];
	}
	std::cout << '\n';

	return 0;
}
