#ifndef IPRODUCT_H
#define IPRODUCT_H

#include<iostream>
#include<cstring>
#include<ctime>
#include<iomanip>


using namespace std;
namespace sdds {
	// an interface for all the products
	class iProduct {
	public:
		virtual ~iProduct() = default;
		virtual int readSku(istream& istr = cin) = 0 ;
		// to reduce the quantity on hand
		virtual int Sku() = 0;
		virtual int operator-=(int qty) = 0;
		// to increase the quantity on hand
		virtual int operator+=(int qty) = 0;
		// returns the price of the produce
		virtual operator double()const = 0;
		// returns if the iProduct is in a good state
		virtual operator bool()const = 0;
		// returns the number of products needed
		virtual int qtyNeeded()const = 0;
		// retuns the quantity on hand
		virtual int qty()const = 0;
		// determines if the iProduct is displayed in a linear format or 
		// descriptive format
		virtual void linear(bool isLinear) = 0;
		// saves the iProduct into a file
		virtual ofstream& save(std::ofstream& ofstr)const = 0;
		// loads an iProduct from a file
		virtual ifstream& load(std::ifstream& ifstr) = 0;
		// displays the iProduct on the screen
		virtual ostream& display(std::ostream& ostr) = 0;
		// reads the iProduct from the console
		virtual istream& read(std::istream& istr = cin) = 0;
		// return true if the sku is a match to the iProduct's sku
		virtual bool operator==(int sku)const = 0;
		// rtrns true if the description is found in the iPorduct's description
		virtual bool operator==(const char* description)const = 0;
		friend ostream& operator<< (ostream& os,  iProduct& R) {
			return R.display(os);
		}
		friend istream& operator>> (istream& is, iProduct& R) {
			return R.read(is);
		}
	};
}
#endif // !1

