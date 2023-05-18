#ifndef  ITEM_H
#define  ITEM_H
#include"iProduct.h"
#include"Status.h"




using namespace std;
namespace sdds {
	// Item implements iProduct
	class Item : public iProduct {
	private:
		// price of an item
		double price;
		// quantity of an item
		int quantity;
		// the total quantity wanted
		int tar_quantity;
		// description of this item
		char* desc;
		bool Linear;
		
	protected:
		// status instance for validation of information of this item
		Status state;
		// stock keeping unit
		int sku;
	public:
		Item();
		Item(Item& R);
		~Item() {
			if (this->desc != nullptr)
				delete[] this->desc;
		}
		bool isLinear() const;
		int qtyNeeded() const ;
		int qty()const ;
		operator double()const ;
		operator bool()const ;
		void linear(bool isLinear);
		int operator-=(int qty);
		virtual int operator+=(int qty);
		void clear();
		bool operator==(int sku)const;
		bool operator==(const char* description)const;
		ofstream& save(std::ofstream& ofstr)const;
		ifstream& load(std::ifstream& ifstr);
		ostream& display(std::ostream& ostr);
		int readSku(istream& istr);
		int Sku();
		istream& read(std::istream& istr);
		void copy(const Item& R);
	};




}
#endif // ! Item_H
