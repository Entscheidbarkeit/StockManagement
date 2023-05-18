#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"Status.h"
#include"Utils.h"
using namespace std;

namespace sdds {
	// constructor for status
	Status::Status(const char* i_description) {
		int length;
		if (i_description == nullptr) {
			this->description = nullptr;
			this->statusCode = 0;
		}
		else {
			length = strlen(i_description);
			this->description = new char[length + 1];
			strcpy(this->description, i_description);
			this->statusCode = 0;
		}
	}
	// = overload for copy functionality
	Status& Status:: operator = (const char* i_description) {
		int length;
		if (this->description != nullptr) {
			delete[] this->description;
			length = strlen(i_description);
			this->description = new char[length + 1];
			strcpy(this->description, i_description);
		}
		else {
			length = strlen(i_description);
			this->description = new char[length + 1];
			strcpy(this->description, i_description);
		}
		return *this;
	}
	// = overload for single status code
	Status& Status:: operator = (int i_code) {
		this->statusCode = i_code;
		return *this;
	}
	// char representation for status
	Status:: operator const char*() const{
		return this->description;
	}
	// int representation for status code
	Status:: operator int() const {
		return this->statusCode;
	}
	// validation for instance
	Status:: operator bool() const {
		if (this->description == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	// reset the instance
	void Status::clear() {
		if (this->description != nullptr) {
			delete[] this->description;
			this->description = nullptr;
		}
			
	}
	// <<overload for output
	ostream& operator<< (ostream& os, const Status& R) {
		if (R.statusCode != 0) {
			os << "ERR#" << R.statusCode << ": " << R.description;
			return os;
		}
		else {
			os << R.description;
			return os;
		}

	}
}