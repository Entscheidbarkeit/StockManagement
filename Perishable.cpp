#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<iomanip>
#include<fstream>
#include"Status.h"
#include"Utils.h"
#include"Item.h"
#include"Perishable.h"


using namespace std;
namespace sdds {
	// a constructor for Perishable
	Perishable::Perishable() {
		this->Instruction = nullptr;
	}
	// copy constructor for Perishable
	Perishable::Perishable(Perishable& R) {
		if (R) {
			this->Instruction = new char[strlen(R.Instruction) + 1];
			strcpy(this->Instruction, R.Instruction);
			this->copy(R);
			this->expiryDate = R.expiryDate;
		}
		else {
			this->Instruction = nullptr;
		}
	}
	// destructor for perishable
	Perishable:: ~Perishable() {
		if (this->Instruction != nullptr) {
			delete[] this->Instruction;
		}
	}
	// = overload for copy constructor
	Perishable& Perishable:: operator=(Perishable& R) {
		if (this->Instruction != nullptr) {
			delete[] this->Instruction;
			this->Instruction = new char[strlen(R.Instruction) + 1];
			strcpy(this->Instruction, R.Instruction);
			this->copy(R);
		}
		else {
			this->Instruction = new char[strlen(R.Instruction) + 1];
			strcpy(this->Instruction, R.Instruction);
			this->copy(R);
		}
		return *this;
	}
	// getter for expriy date
	Date& Perishable:: expiry() {
		return this->expiryDate;
	}
	// save the data to the ofstream(overwrite of save() from Item)
	ofstream& Perishable:: save(std::ofstream& ofstr)const {
		if (this->state) {
			Item::save(ofstr);
			ofstr << '\t';
			if (this->Instruction != nullptr) {
				ofstr << this->Instruction;
			}
			ofstr << '\t';
			this->expiryDate.write(ofstr);
			return ofstr;
		}
		else {
			return ofstr;
		}
	}
	// load data from ifstream(overwrite of load() from Item)
	ifstream& Perishable:: load(std::ifstream & ifstr) {
		if (this->Instruction != nullptr) {
			delete[] this->Instruction;
			this->Instruction = nullptr;
		}
		string tmp,instruction,date,isIn;
		unsigned int i,length;
		Item::load(ifstr);
		if (ifstr.eof() == false) {
			bool end = false;
			bool isNNum = false;
			// tmp contains a line from the ifstream
			while (end == false) {
				tmp += ifstr.get();
				if (tmp[tmp.length() - 1] == '\n') {
					end = true;
				}
			}
			isIn = tmp;
			// delete the '\t' from input
			isIn = ut.deleteMem(isIn, '\t');
			for (i = 0;i < isIn.length();i++) {
				if (isIn[i] < 48 || isIn[i] > 57) {
					isNNum = true;
					break;
				}
			}
			length = tmp.length();
			// extrace instruction part from string
			if (isNNum == true) {
				for (i = 0;i < length;i++) {
					if (tmp[i] < 48 || tmp[i]>57 || tmp[i] != '\t') {
						if (tmp[i] != '\t')
							instruction += tmp[i];
						else
							break;
					}
				}
				instruction = ut.deleteMem(instruction, '\t');
				this->Instruction = new char[instruction.length() + 1];
				strcpy(this->Instruction, instruction.c_str());
			}
			else
				this->Instruction = nullptr;
			// extract the date part
			for (i=i; i < length;i++) {
				if (tmp[i] == '\t' || tmp[i] == '\n')
					if (date.length() == 0);
					else break;
				else {
					date += tmp[i];
				}
			}
			string year;
			year = date[0];
			year += date[1];
			this->expiryDate.Year = atoi(year.c_str());
			this->expiryDate.Year += 2000;
			string month;
			month = date[2];
			month += date[3];
			this->expiryDate.Month = atoi(month.c_str());
			string day;
			day = date[4];
			day += date[5];
			this->expiryDate.Day = atoi(day.c_str());
		}
		if (ifstr.bad())
			this->state = "Input file stream read (perishable) failed!";
		return ifstr;
	}
	// a string representation for instance
	ostream& Perishable:: display(std::ostream& ostr) {
		if (!this->state) {
			ostr << this->state;
			return ostr;
		}
		else {
			this->expiryDate.formatted(true);
			if (this->isLinear()) {
				Item::display(ostr);
				if (this->Instruction == nullptr) {
					ostr << " " << this->expiryDate;
				}
				else {
					if (strlen(this->Instruction) == 0)
						ostr << " " << this->expiryDate;
					else
					ostr << "*" << this->expiryDate;
				}
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";
				ostr << this->expiryDate;
				ostr << endl;
				if (this->Instruction != nullptr) {
					if (strlen(this->Instruction) == 0);
					else
						ostr << "Handling Instructions: " << this->Instruction<<endl;
				}
				else {
					ostr << endl;
				}
			}
		}
		this->expiryDate.formatted(false);
		return ostr;
	}
	// read the instruction and expriy date from user and their validation
	istream& Perishable:: read(std::istream& istr) {
		Item::read(istr);
		char instruction[101];
		string tmp;
		if (this->Instruction != nullptr) {
			delete[] this->Instruction;
			this->Instruction = nullptr;
		}
		cout << "Expiry date (YYMMDD): ";
		this->expiryDate.read(istr);
		cout << "Handling Instructions, ENTER to skip: ";
		char fst = istr.get();
		if (fst != '\n') {
			tmp += fst;
			istr.getline(instruction, 100);
			tmp += instruction;
			this->Instruction = new char[tmp.length() + 1];
			strcpy(this->Instruction, tmp.c_str());
			cout << endl;
		}
		else {
			cout << endl;
		}
		if (istr.bad()) {
			this->state = "Perishable console date entry failed!";
		}
		return istr;
	}
}