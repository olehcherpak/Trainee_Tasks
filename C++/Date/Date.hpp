#ifndef DATE_HPP
#define DATE_HPP

#include <set>
#include <iostream>

#define LEAP_YEAR_LENGTH 366
#define YEAR_LENGTH 365

class Date
{
	const std::set<int> shortMounthes = {4, 6, 9, 11};
	int day;
	int mounth;
	int year;

	bool leapYear(const int&) const;
	int mounthLength(const int&, const int&) const;

public:
	Date(const int&, const int&, const int&);
	~Date();
	int getDay() const;
	int getMounth() const;
	int getYear() const;
};

std::ostream& operator<<(std::ostream&, const Date&); 

class unvalid_date_exception
{};
#endif
