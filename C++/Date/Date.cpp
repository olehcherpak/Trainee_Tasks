#include <set>
#include <iostream>

#include "Date.hpp"

#define MAXMOUNTH 12

Date::Date(const int& _day, const int& _mounth, const int& _year) {
    if (_year == 0) {
        throw invalid_date_exception();
    }
    year = _year;

    if (_mounth <= 0 || _mounth > MAXMOUNTH) {
        throw invalid_date_exception();
    }
    mounth = _mounth;

    if (_day <= 0 || _day > mounthLength(mounth, year)) {
        throw invalid_date_exception();
    }
    day = _day;
}

Date::~Date() {

}

int Date::mounthLength(const int& mounth, const int& year) const {
    if (mounth == 2) {
        if (leapYear(year)) {
            return 29;
        } else {
            return 28;
        }
    }

    if (shortMounthes.find(mounth) != shortMounthes.end()) {
        return 30;
    }

    return 31;
}

bool Date::leapYear(const int& year) const {
    if (year % 400 == 0) {
        return true;
    }

    if (year % 100 == 0) {
        return false;
    }

    if (year % 4 == 0) {
        return true;
    }

    return false;
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

std::ostream& operator<<(std::ostream& os, const Date& dt) {
    os << dt.getDay() << '/' << dt.getMounth() << '/' << dt.getYear();
    return os;
}
