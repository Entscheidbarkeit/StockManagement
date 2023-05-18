#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include"Status.h"
#include"Utils.h"
#include"Date.h"
using namespace std;
#define MAXYEAR 2030
namespace sdds {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int cYear = 2022;
	int cMonth = 3;
	int cDay = 31;
	// a validation for the input of date, whereas the day must be inside the range of a certain month in a certain year
	bool Date::validate() {
		if (this->Year< cYear || this->Year> MAXYEAR) {
			this->State = "Invalid year in date";
			this->State = 1;
		}
		if (this->Month < 1 || this->Month>12) {
			this->State = "Invalid month in date";
			this->State = 2;
		}
		if (Year == 2024||Year ==2028) {
			if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) {
				if (Day < 1 || Day> 31) {
					this->State = "Invalid day in date";
					this->State = 3;
				}
			}
			if (Month == 2) {
				if (Day < 1 || Day> 29) {
					this->State = "Invalid day in date";
					this->State = 3;
				}
			}
			if (Month == 4 || Month == 6 || Month == 9 || Month == 11) {
				if (Day < 1 || Day> 30) {
					this->State = "Invalid day in date";
					this->State = 3;
				}
			}
		}
		else {
			if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) {
				if (Day < 1 || Day> 31) {
					this->State = "Invalid day in date";
					this->State = 3;
				}
			}
			if (Month == 2) {
				if (Day < 1 || Day> 28) {
					this->State = "Invalid day in date";
					this->State = 3;
				}
			}
			if (Month == 4 || Month == 6 || Month == 9 || Month == 11) {
				if (Day < 1 || Day> 30) {
					this->State = "Invalid day in date";
					this->State = 3;
				}
			}
		}
		if (this->State)
			return true;
		else
			return false;
	}
	// returns the total days of current time
	int Date::uniDate() {
		return Year * 372 + Month * 31 + Day;
	}
	// constructor for date
	Date::Date(int y, int m, int d,bool f) {
		if (y == 0) 
			this->Year = cYear;
		else
			this->Year = y;
		if (m == 0)
			this->Month = cMonth;
		else
			this->Month = m;
		if (d == 0)
			this->Day = cDay;
		else
			this->Day = d;
		this->Formatted = f;
	}
	// a bool overload for date
	Date:: operator bool() const {
		return this->State;
	}
	// a == overload for equals of two instances
	bool Date:: operator ==(Date& r) {
		if (this->uniDate() == r.uniDate())
			return true;
		else
			return false;
	}
	//a != overload for inequality of two instances
	bool Date:: operator !=(Date& r) {
		if (this->uniDate() != r.uniDate())
			return true;
		else
			return false;
	}
	// a < overload for smaller than
	bool Date:: operator <(Date& r) {
		if (this->uniDate() < r.uniDate())
			return true;
		else
			return false;
	}
	// a <= overload for smaller equal
	bool Date:: operator <=(Date& r) {
		if (this->uniDate() <= r.uniDate())
			return true;
		else
			return false;
	}
	// a > overload for greater than
	bool Date:: operator >(Date& r) {
		if (this->uniDate() > r.uniDate())
			return true;
		else
			return false;
	}
	// a <= overload for greater equal
	bool Date:: operator >=(Date& r) {
		if (this->uniDate() >= r.uniDate())
			return true;
		else
			return false;
	}
	// return the status instance of date
	Status& Date::state() {
		return this->State;
	}
	// setter for formatted
	Date& Date::formatted(bool flag) {
		this->Formatted = flag;
		return *this;
	}
	// print the string representation for date with different formats
	ostream& Date::write(ostream& os) const{
		if (this->Formatted == true) {
			os << this->Year << '/' << setw(2) << setfill('0') << this->Month << '/' << setw(2) << setfill('0') << this->Day;
			return os;
		}
		else {
			os << this->Year%2000 << setw(2) << setfill('0') << this->Month << setw(2) << setfill('0') << this->Day;
			return os;
		}
	}
	// a reader for date, whereas the input with less than 4 interger is interpreted as days, 4 as days and month, 6 as days month years.
	istream& Date::read(istream& is) {
		int date;
		is >> date;
		int tmp = date;
		int count = 0;
		if (is.fail() == true) {
			this->State = "Invalid date value";
			return is;
		}
		while (tmp != 0) {
			tmp /= 10;
			count++;
		}
		if (count < 4) {
			this->Year = cYear;
			this->Month = 0;
			this->Day = count;
			is.clear(ios::failbit);
			this->validate();
			return is;
		}
		if (count == 4) {
			this->Year = cYear;
			this->Month = (date-date%100)/100;
			this->Day = date%100;
			is.clear();
		}
		if (count == 6) {
			this->Year = 2000+(date - date%10000)/10000;
			this->Month = ((date / 100) % 100);
			this->Day = date % 100;
			is.clear();
		}
		if (this->validate() == false) {
			is.clear(ios::failbit);
		}
		is.ignore(1000, '\n');
		return is;
	}
	// << overload for output
	ostream& operator<<(ostream& os, Date r) {
		return r.write(os);
	}
	// >> overload for input
	istream& operator>>(istream& is, Date& r) {
		return r.read(is);
	}

}
