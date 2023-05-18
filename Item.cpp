#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<iomanip>
#include<fstream>
#include"Status.h"
#include"Utils.h"
#include"Item.h"


using namespace std;
namespace sdds {
	// the request for Linear
	bool Item:: isLinear() const {
		return this->Linear;
	}
	// a constructor for item
	Item::Item() {
		this->desc = nullptr;
		this->Linear = false;
		this->price = 0;
		this->quantity = 0;
		this->sku = 0;
		this->tar_quantity = 0;
	}
	// a copy constructor for item
	Item::Item(Item& R) {
		this->desc = new char[strlen(R.desc) + 1];
		strcpy(this->desc, R.desc);
		this->Linear = R.Linear;
		this->price = R.price;
		this->quantity = R.quantity;
		this->sku = R.sku;
		this->tar_quantity = R.tar_quantity;
	}
	// getter for quantity needed
	int Item::qtyNeeded() const {
		return this->tar_quantity;
	}
	// getter for the current quantity
	int Item::qty()const {
		return this->quantity;
	}
	// getter for price
	Item:: operator double()const {
		return this->price;
	}
	// validation for this item
	Item:: operator bool()const {
		if (this->desc == nullptr)
			return false;
		else
			return this->state;
	}
	// setter for Linear
	void  Item::linear(bool isLinear) {
		this->Linear = isLinear;
	}
	int  Item::  operator-=(int qty) {
		this->quantity -= qty;
		return this->sku;
		
	}
	// += overload for increse of quantity
	int  Item::  operator+=(int qty) {
		this->quantity += qty;
		return this->sku;
	}
	// clear of the validation state 
	void  Item::clear() {
		this->state.clear();
	}
	// == overload for equanlity of sku of two instances
	bool  Item:: operator==(int sku)const {
		if (this->sku == sku)
			return true;
		else
			return false;
	}
	// == overload for equanlity of description of two instances
	bool Item:: operator==(const char* description)const {
		if (this->desc == nullptr || description == nullptr)
			return false;
		else {
			if (strstr(this->desc, description) != nullptr)
				return true;
			else {
				return false;
			}
		}
	}
	// save the data to the ofstream
	ofstream& Item::save(std::ofstream& ofstr)const {
		if (this->state) {
			ofstr << this->sku << '\t' << this->desc << '\t' << this->quantity << '\t' << this->tar_quantity << '\t' << this->price;
			return ofstr;
		}
		else {
			return ofstr;
		}
	}
	// load data from ifstream
	ifstream& Item::load(std::ifstream& ifstr) {
		if (this->desc != nullptr) {
			delete[] this->desc;
			this->desc = nullptr;
		}
		int i = 0;
		int tab = 0;
		string sku, desc, quantity, tarQ, price,tmp;
		while (tab != 5) {
			if (ifstr.eof() == false) {
				tmp += ifstr.get();
				if (tmp[tmp.length() - 1] == '\t' || tmp[tmp.length() - 1] == '\n')
					tab++;
			}
			else break;
		}
		if (ifstr.eof() == false) {
			int length = tmp.length();
			for (i = 0;i < length;i++) {
				if (tmp[i] != '\t') {
					sku += tmp[i];
				}
				else
					break;
			}
			this->sku = atoi(sku.c_str());
			for (i += 1;i < length;i++) {
				if (tmp[i] != '\t') {
					desc += tmp[i];
				}
				else
					break;
			}
			this->desc = new char[desc.length() + 1];
			strcpy(this->desc, desc.c_str());
			for (i += 1;i < length;i++) {
				if (tmp[i] != '\t') {
					quantity += tmp[i];

				}
				else
					break;
			}
			this->quantity = atoi(quantity.c_str());
			for (i += 1;i < length;i++) {
				if (tmp[i] != '\t') {
					tarQ += tmp[i];

				}
				else
					break;
			}
			this->tar_quantity = atoi(tarQ.c_str());
			for (i += 1;i < length;i++) {
				if (tmp[i] != '\n' || tmp[i] != '\t') {
					price += tmp[i];

				}
				else
					break;
			}
			this->price = atof(price.c_str());
		}
		if (ifstr.bad())
			this->state = "Input file stream read failed!";
		return ifstr;
	}
	// string represtation for the item. output destination is the parameter
	ostream& Item::display(std::ostream& ostr) {
		if (!this->state) {
			ostr << this->state;
			return ostr;
		}
		int i = 0;
		if (this->Linear == false) {
			ostr << "AMA Item:" << endl;
			ostr << this->sku << ": " << this->desc << endl;
			ostr << "Quantity Needed: " << this->tar_quantity << endl;
			ostr << "Quantity Available: " << this->quantity << endl;
			ostr << "Unit Price: $" << setiosflags(ios::fixed) << setprecision(2) << this->price << endl;
			return ostr;
		}
		else {
			ostr << this->sku << " | ";
			if (strlen(this->desc) > 35) {
				char sub[36];
				while (i < 35) {
					sub[i] = this->desc[i];
					i++;
				}
				sub[35] = '\0';
				ostr << setw(35) << setfill(' ') << left << sub;
				ostr << right << " | " << setw(4) << setfill(' ') << this->quantity << " | " << setw(4) << setfill(' ') << this->tar_quantity << " | " << setw(7) << setfill(' ') << this->price << " |";
			}
			else {
				ostr << setw(35) << setfill(' ') << left << this->desc;
				ostr << right << " | " << setw(4)<<setfill(' ') << this->quantity << " | " << setw(4) << setfill(' ') << this->tar_quantity << " | " << setw(7) << setfill(' ') << this->price << " |";
			}
			return ostr;
		}
	}
	// read sku from user and validation for the read sku
	int  Item::readSku(istream& istr) {
		string ip;
		int i;
		bool flag = true;
		bool flagValid = true;
		int length;
		cout << "SKU: ";
		while (flag|| flagValid) {
			flag = false;
			flagValid = false;
			string tmp;
			istr >> tmp;
			length = tmp.length();
			for (i = 0;i < length;i++) {
				if (tmp[i] < 48 || tmp[i]>57) {
					cout << "Invalid Integer, retry: ";
					flag = true;
					break;
				}
			}
			if (flag == false) {
				if (atoi(tmp.c_str()) < 99999 && atoi(tmp.c_str()) > 40000) {
					flagValid = false;
				}
				else {
					flagValid = true;
					cout << "Value out of range [40000<=val<=99999]: ";
				}
			}
			if (flag == false && flagValid == false) {
				this->sku = atoi(tmp.c_str());
				return atoi(tmp.c_str());
			}
		}
		return 0;
	}
	// read an item from user
	istream& Item::read(std::istream& istr) {
		if (this->desc != nullptr)
			delete[] this->desc;
		cout << "AMA Item:" << endl << "SKU: "<<this->sku<<endl;
		cout << "Description: ";
		char Desc[101];
		getchar();
		istr.getline(Desc,101);
		this->desc = new char[strlen(Desc) + 1];
		strcpy(this->desc, Desc);
		cout << "Quantity Needed: ";
		this->tar_quantity = ut.getInt(1, 9999);
		cout << "Quantity On Hand: ";
		this->quantity = ut.getInt(0, this->tar_quantity);
		cout << "Unit Price: $";
		this->price = ut.getDouble(0, 9999);
		return istr;
	}
	// copy the an instance to another.
	void Item::copy(const Item& R) {
		if (this->desc != nullptr) {
			delete[] this->desc;
			this->desc = new char[strlen(R.desc) + 1];
			strcpy(this->desc, R.desc);
			this->Linear = R.Linear;
			this->price = R.price;
			this->quantity = R.quantity;
			this->tar_quantity = R.tar_quantity;
			this->sku = R.sku;
			this->state = this->state;
		}
		else {
			this->desc = new char[strlen(R.desc) + 1];
			strcpy(this->desc, R.desc);
			this->Linear = R.Linear;
			this->price = R.price;
			this->quantity = R.quantity;
			this->tar_quantity = R.tar_quantity;
			this->sku = R.sku;
			this->state = this->state;
		}
	}
	// getter for sku
	int Item::Sku() {
		return this->sku;
	}

}