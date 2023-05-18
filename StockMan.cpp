#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
#include<iomanip>
#include<fstream>
#include"Status.h"
#include"Utils.h"
#include"Date.h"
#include"Menu.h"
#include"StockMan.h"
#include"iProduct.h"
#include"Item.h"
#include"Perishable.h"


using namespace std;
namespace sdds {
	// the globla variable for products
	iProduct* ipArr[500] = { nullptr };
	int validNum = 0; // the number of valid products
	string empty;
	// the constructer for stock management
	StockMan::StockMan(const char* fN, unsigned int opt) {
		this->men = new Menu(fN, opt);
		this->fileName = nullptr;
	}
	// list for all the products, with an extra number input, the detail of a product will be shown
	int StockMan::list(const char* sub_desc) {
		int printed = 0;
		int i = 0;
		if (sub_desc == nullptr) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (i = 0;i < validNum;i++) {
				if (ipArr[i] == nullptr);
				else {
					ipArr[i]->linear(true);
					cout << setw(4) << setfill(' ') << i + 1 << " | ";
					cout << *ipArr[i] << endl;
					printed++;
				}
			}
			if (printed == 0) {
				cout << "The list is emtpy!";
				return printed;
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			cout << "Enter row number to display details or <ENTER> to continue:\n> ";
			string op;
			bool flag = true;
			while (flag == true) {
				cin.clear();
				cin.sync();
				getchar();
				cin.get(op[0]);
				if (op[0] == '\n') {
					cout << endl;
					return printed;
				}
				if (op[0] < 48 || op[0] >57) {
					cout << "Please enter valid row number: ";
				}
				if (op[0] < 57 && op[0]>48)
					flag = false;
			}
			int row = atoi(op.c_str());
			ipArr[row - 1]->linear(false);
			cout << *ipArr[row - 1];
			ipArr[row - 1]->linear(true);
		}
		else {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (i = 0;i < validNum;i++) {
				if (ipArr[i] == nullptr);
				else {
					if (*ipArr[i] == sub_desc) {
						ipArr[i]->linear(true);
						cout << setw(4) << setfill(' ') << i + 1 << " | ";
						cout << *ipArr[i] << endl;
						printed++;
					}
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		}
		if (printed == 0) {
			cout << "The list is emtpy!";
			return printed;
		}
		return printed;
	}
	// print the menu
	unsigned int StockMan::menu() {
			if (this->fileName == nullptr) {
				cout << "Aid Management System\nDate: "<<Date(0,0,0,true)<<"\nData file: "<<"No file" << "\n---------------------------------\n";
			}
			else {
				cout << "Aid Management System\nDate: " << Date(0, 0, 0, true) << "\nData file: " << this->fileName << "\n---------------------------------\n";
			}
			return this->men->run();
	}
	// main entry point for user interface, with a number input, the user can chose different functions
	void StockMan::run() {
		bool flag = false;
		int opt = 0;
		int i;
		while (flag == false) {
			opt = menu();
			if (opt == 0) {
				cout << "Exiting Program!" << endl;	
				if (this->fileName == nullptr) {
					this->men->clear();
					delete this->men;
					flag = true;
				}
				else {
					delete[] this->fileName;
					this->men->clear();
					delete this->men;
					flag = true;
				}
				if (validNum != 0) {
					for (i = 0;i < validNum;i++) {
						if (ipArr[i] != nullptr) {
							delete ipArr[i];
							ipArr[i] = nullptr;
						}
					}
				}
			}
			if (opt == 1) {
				if (this->fileName == nullptr) {
					opt = 7;
				}
				else {
					cout << endl << "****List Items****" << endl;
					list();
				}
			}
			if (opt == 2) {
				if (this->fileName == nullptr) {
					opt = 7;
				}
				else {
					cout << endl << "****Add Item****" << endl;
					addItem();
				}
			}
			if (opt == 3) {
				if (this->fileName == nullptr) {
					opt = 7;
				}
				else {
					cout << endl << "****Remove Item****" << endl;
					removeItem();
				}
			}
			if (opt == 4) {
				if (this->fileName == nullptr) {
					opt = 7;
				}
				else {
					cout << endl << "****Update Quantity****" << endl;
					updateQuantity();
					save(this->fileName);
				}
			}
			if (opt == 5) {
				if (this->fileName == nullptr) {
					opt = 7;
				}
				else {
					cout << endl << "****Sort****" << endl;
					Sort();
					save(this->fileName);
				}
			}
			if (opt == 6) {
				if (this->fileName == nullptr) {
					opt = 7;
				}
				else {
					cout << endl << "****Ship Items****" << endl;
					ShipOrders();
				}
			}
			if (opt == 7) {
				cout << endl << "****New/Open Aid Database****" << endl ;
				load();
			}
		}
	}
	// save the changed data to file
	void StockMan::save(const char* fileName) {
		int i = 0;
		if (fileName == nullptr) {
			return;
		}
		else {
			ofstream of(fileName);
			while (i != validNum) {
				if (ipArr[i] != nullptr) {
					ipArr[i]->save(of);
					of << '\n';
				}
				i++;
			}
		}
	}
	// deallocation of all products before exit
	void StockMan::deallocate() {
		int i = 0;
		while (i != validNum) {
			ipArr[i]->~iProduct();
			ipArr[i] = nullptr;
			i++;
		}
		validNum = 0;
	}
	// load all the products from file
	bool StockMan::load(const char* fileName) {
		if (this->fileName != nullptr) {
			ifstream ifs(this->fileName);
			string ip;
			bool read = true;
			while (getline(ifs, ip)) {
				if (ip[0] < 48 || ip[0]>57)
					read = false;
				else {
					if (ip[0] >= '1' && ip[0] <= '3') {
						ipArr[validNum] = new Perishable;
						validNum++;
					}
					else {
						ipArr[validNum] = new Item;
						validNum++;
					}

				}
			}
			if (read == false)
				return false;
			else {
				ifs.clear();
				ifs.seekg(0, ios::beg);
				int i = 0;
				for (i = 0; i < validNum;i++) {
					ipArr[i]->load(ifs);
					if (!ipArr[i]) {
						ipArr[i]->~iProduct();
						ipArr[i] = nullptr;
					}
				}
				return true;
			}
		}
		else{
			string newfile;
			cout << "Enter file name: ";
			cin >> newfile;
			ifstream ifs(newfile);
			int ip = -1;
			if (ifs.fail()) {
				cout << "Failed to open " << newfile << " for reading!" << endl;;
				cout << "Would you like to create a new data file?" << endl;
				cout << "1- Yes!\n0 - Exit\n> ";
				cin >> ip;
				if (ip == 1) {
					ofstream of;
					of.open(newfile);
					of.close();
				}
				return false;
			}
			else {
				string ip;
				bool read = true;
				while (getline(ifs, ip)) {
					if (ip[0] < 48 || ip[0]>57)
						read = false;
					else {
						if (ip[0] >= '1' && ip[0] <= '3') {
							ipArr[validNum] = new Perishable;
							validNum++;
						}
						else {
							ipArr[validNum] = new Item;
							validNum++;
						}
					}
				}
				if (read == false)
					return false;
				else {
					ifs.clear();
					ifs.seekg(0, ios::beg);
					int i = 0;
					for (i = 0; i < validNum;i++) {
						ipArr[i]->load(ifs);
						if (!ipArr[i]) {
							ipArr[i]->~iProduct();
							ipArr[i] = nullptr;
						}
					}
					cout << validNum << " records loaded!" << endl << endl;
					if (this->fileName == nullptr) {
						this->fileName = new char[newfile.length() + 1];
						strcpy(this->fileName, newfile.c_str());
					}
					else {
						delete[] this->fileName;
						this->fileName = new char[newfile.length() + 1];
						strcpy(this->fileName, newfile.c_str());
					}
					return true;
				}
			}
		}
	}
	// search a product with given sku
	int StockMan::search(int sku) const {
		int i;
		bool found = false;
		for (i = 0;i < validNum;i++) {
			if (*ipArr[i] == sku) {
				found = true;
				break;
			}
		}
		if (found == false)
			return -1;
		else {
			return i;
		}
	}
	// add a product from user
	void StockMan:: addItem() {
		if (validNum == 501) {
			cout << "Database full!" << endl;
		}
		else {
			cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ";
			int ip = ut.getInt(0, 2);
			if (ip == 1) {
				ipArr[validNum] = new Perishable;
				ipArr[validNum]->readSku();
				int found = search(ipArr[validNum]->Sku());
				if (found != -1) {
					cout << "Sku: "<<ipArr[validNum]->Sku() <<" is already in the system, try updating quantity instead.\n\n";
					delete ipArr[validNum];
					ipArr[validNum] = nullptr;
				}
				else {
					ipArr[validNum]->read();
					if (!ipArr[validNum]) {
						cout << ipArr[validNum];
						delete ipArr[validNum];
						ipArr[validNum] = nullptr;
					}
					else {
						validNum++;
						save(this->fileName);
					}
				}
				return;
			}
			if (ip == 2) {
				ipArr[validNum] = new Item;
				ipArr[validNum]->readSku();
				int found = search(ipArr[validNum]->Sku());
				if (found != -1) {
					cout << "Sku: " << ipArr[validNum]->Sku() << " is already in the system, try updating quantity instead.\n\n";
					delete ipArr[validNum];
					ipArr[validNum] = nullptr;
				}
				else {
					ipArr[validNum]->read();
					if (!ipArr[validNum]) {
						cout << ipArr[validNum];
						delete ipArr[validNum];
						ipArr[validNum] = nullptr;
					}
					else {
						validNum++;
						save(this->fileName);
					}
				}
				return;
			}
			if (ip == 0) {
				cout << "Aborted\n";
				return;
			}
		}
	}
	// remove item by user input
	void StockMan::removeItem() {
		int i,j;
		int sku,found,ip;
		cout << "Item description: ";
		string desc;
		cin >> desc;
		i = list(desc.c_str());
		if (i == 0) {
			cout << "Description not found!" << endl;
		}
		else {
			cout << "Enter SKU: ";
			sku = ut.getInt();
			found = search(sku);
			if (found != -1) {
				cout << "Following item will be removed: "<<endl;
				ipArr[found]->linear(false);
				cout << *ipArr[found] << endl;
				cout << "Are you sure?\n1- Yes!\n0- Exit\n> ";
				ip = ut.getInt(0, 1);
				if (ip == 1) {
					delete ipArr[found];
					ipArr[found] = nullptr;
					cout << "Item removed!" << endl << endl;
					save(this->fileName);
					for (j = 0;j < validNum;j++) {
						if (ipArr[j] != nullptr) {
							delete ipArr[j];
							ipArr[j] = nullptr;
						}
					}
					validNum = 0;
					load(this->fileName);
				}
				if (ip == 0) {
					cout << "Aborted!"<<endl;
				}
			}
		}
	}
	// update the quantity from user
	void StockMan::updateQuantity() {
		int i;
		int sku, found, ip,change;
		cout << "Item description: ";
		string desc;
		cin >> desc;
		i = list(desc.c_str());
		if (i == 0) {
			cout << "No matches found!\n" << endl;
			return;
		}
		else {
			cout << "Enter SKU: ";
			sku = ut.getInt();
			found = search(sku);
			if (found == -1) {
				cout << "SKU not found!\n" << endl;
				return;
			}
			else {
				cout << "1- Add\n2- Reduce\n0- Exit\n> ";
				ip = ut.getInt(0, 2);
				if (ip == 1) {
					if (ipArr[found]->qty() == ipArr[found]->qtyNeeded()) {
						cout << "Quantity Needed already fulfilled!" << endl << endl;
						return;
					}
					else {
						cout << "Quantity to add: ";
						change = ut.getInt(1, ipArr[found]->qtyNeeded() - ipArr[found]->qty());
						*ipArr[found] += change;
						cout << change << " items added!" << endl<<endl;
						return;
					}
				}
				if (ip == 2) {
					if (ipArr[found]->qty() == 0) {
						cout << "Quaintity on hand is zero!\n" << endl << endl;
					}
					else {
						cout << "Quantity to reduce: ";
						change = ut.getInt(1, ipArr[found]->qty());
						*ipArr[found] -= change;
						cout << change << " items removed!"<<endl<<endl;
					}
				}
				if(ip == 0) {
					cout << "Aborted!\n" << endl;
					return;
				}
			}
		}
	}
	// sort the item by the lacking quantity
	void StockMan::Sort() {
		int i, j;
		iProduct* tmp = nullptr;
		for (i = 0;i < validNum;i++) {
			for (j = 0;j < validNum-1;j++) {
				if (ipArr[j]->qtyNeeded() - ipArr[j]->qty() < ipArr[j + 1]->qtyNeeded() - ipArr[j + 1]->qty()) {
					tmp = ipArr[j];
					ipArr[j] = ipArr[j + 1];
					ipArr[j + 1] = tmp;
				}
			}
		}
		cout << "Sort completed!" << endl << endl;;
		return;
	}
	// save the shipping orders to a file
	void StockMan::ShipOrders(){
		int i,j,printed;
		printed = 0;
		ofstream of("shippingOrder.txt");
		of << "Shipping Order, Date: " << Date(0, 0, 0, true) << endl;
		of << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		of << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		for (i = 0; i < validNum;i++) {
			if (ipArr[i]->qty() == ipArr[i]->qtyNeeded()) {
				ipArr[i]->linear(true);
				printed++;
				of << setw(4) << setfill(' ') << printed << " | ";
				of << *ipArr[i] << endl;
				delete ipArr[i];
				ipArr[i] = nullptr;
				for (j = i;j < validNum;j++) {
					ipArr[j] = ipArr[j + 1];
				}
				delete ipArr[validNum - 1];
				ipArr[validNum - 1] = nullptr;
				validNum--;
				i--;
			}
		}
		of << "-----+-------+-------------------------------------+------+------+---------+-----------"<<endl;
		cout << "Shipping Order for " << printed << " times saved!" << endl << endl;
		save(this->fileName);
		return;
	}
}