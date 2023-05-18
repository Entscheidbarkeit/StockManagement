#ifndef DATE_H
#define DATE_H
#include<ctime>
#include<iostream>
#include"Status.h"

using namespace std;
namespace sdds {
	// the date class can print different date format as required
	class Date {
	private:
		bool validate();
		int	uniDate();
	public:
		int Year;
		int Month;
		int Day;
		bool Formatted;
		Status State;
		Date(int y = 0, int m = 0, int d = 0, bool f = false);
		bool operator ==(Date& r);
		bool operator !=(Date& r);
		bool operator <(Date& r);
		bool operator <=(Date& r);
		bool operator >(Date& r);
		bool operator >=(Date& r);
		Status& state();
		Date& formatted(bool flag);
		operator bool() const;
		ostream& write(ostream& os)const;
		istream& read(istream& is = cin);
	};
	ostream& operator<<(ostream& os, Date r);
	istream& operator>>(istream& is, Date& r);
}



#endif // !DATE_H
