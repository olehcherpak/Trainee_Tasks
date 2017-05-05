#include <iostream>
#include "Date.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
	Date today(15, 5, 2016);
    Date happybirthday(17, 1, 1989);
    Date blackDay(29, 2, 1600);

    cout << today << endl << happybirthday << endl << blackDay << endl;

    try {
        Date date(99, 8, 2013); // wrong day
    } catch (...) {
        cout << "wow!" << endl;
    }
    try {
        Date date(29, 99, 2013); // wrong month
    } catch (...) {
        cout << "wow!" << endl;
    }
    try {
        Date date(29, 8, 0); // wrong year
    } catch (...) {
        cout << "wow!" << endl;
    }
    try {
        Date date(29, 2, 1700); // wrong leap day
    } catch (...) {
        cout << "wow!" << endl;
    }
    try {
        Date date(29, 2, 1900); // wrong leap day
    } catch (...) {
        cout << "wow!" << endl;
    }
	return 0;
}
