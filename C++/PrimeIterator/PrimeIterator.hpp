#ifndef PRIMEIRETATOR_HPP
#define PRIMEIRETATOR_HPP

class PrimeIterator
{
public:
	PrimeIterator(const int&, const int&);
	~PrimeIterator();
 	int getIndex() const;
   	void next();
   	void prev();
   	int value();
   	bool over() const;
   	bool first() const;
   	int operator++();
   	int operator++(int);
   	int operator--();
   	int operator--(int);
   	int operator*();
private:
	int numberValue;
	int index;
	int start;
	int finish;
	int lastValue;
	int firstValue;
};

class unvalid_data_exception {};

#endif
