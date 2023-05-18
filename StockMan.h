#ifndef  STOCKMAN_H
#define  STOCKMAN_H
#include<iostream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include"Status.h"
#include"Utils.h"
#include"Date.h"
#include"Menu.h"
#include"iProduct.h"
#include"Item.h"
#include"Perishable.h"


using namespace std;
namespace sdds {
	// an instance is the entry point for all the functionality
	class StockMan {
		// the file to be used
		char* fileName;
		// the menu
		Menu* men;
		private:
		unsigned int menu();
	private:
		void save(const char* fileName);
		void deallocate();
		bool load(const char* fileName = nullptr);
	public:
		void run();
		StockMan(const char* fN = "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n", unsigned int opt = 7);
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void addItem();
		void removeItem();
		void updateQuantity();
		void Sort();
		void ShipOrders();
	};
}
#endif 
