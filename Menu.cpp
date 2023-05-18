#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include"Status.h"
#include"Utils.h"
#include"Date.h"
#include"Menu.h"

using namespace std;
namespace sdds {
	// the constructor for Menu
	Menu:: Menu(const char* list, unsigned int opt) {
		if (list == nullptr || opt > 15)
			this->list = nullptr;
		else {
			int length = strlen(list);
			this->list = new char[length + 1];
			strcpy(this->list, list);
			this->options = opt;
		}
	}
	// reset the instance 
	void Menu:: clear() {
		if (this->list != nullptr)
			delete[] this->list;
	}
	// start the menue with an extra exit option
	int Menu::run() {
		cout << this->list;
		cout << "0- Exit" << endl;
		cout << "> ";
		// get user input
		int ip = ut.getInt(0, this->options);
		return ip;
	}
}