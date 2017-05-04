#include "Date.hpp"
#include <set>
#include <iostream>

#define MAXMONTH 12

Date::Date(const int& _day, const int& _mounth, const int& _year) {
	if (_year < 0) {
		throw unvalid_date_exception();
	} 
	year = _year;

	if (_mounth <= 0 && _mounth > MAXMONTH) {
		throw unvalid_date_exception();
	}
	mounth = _mounth;

	if (_day <= 0 && _day > mounthLength(mounth, year)) {
		throw unvalid_date_exception();
	}
	day = _day;
}

Date::~Date() {

}

int Date::mounthLength(const int& m, const int& y) const {
	if (m == 2) {
		if (leapYear(y)) {
			return 29;
		} else {
			return 28;
		}
	}

	if (shortMounthes.find(m) != shortMounthes.end()) {
		return 30;
	}

	return 31;
}

bool Date::leapYear(const int& y) const {
	if (y % 4 == 0) {
        if (y % 100 == 0) {
            if (y % 400 == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

int Date::getDay() const {
	return day;
}

int Date::getMounth() const {
	return mounth;
}

int Date::getYear() const {
	return year;
}

std::ostream& operator<<(std::ostream& os, const Date& dt)  
{  
    os << dt.getDay() << '/' << dt.getMounth() << '/' << dt.getYear();  
    return os;  
}  
