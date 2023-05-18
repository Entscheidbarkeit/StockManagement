#ifndef PERISHABLE_H
#define PERISHABLE_H

#include"Date.h"
#include"Item.h"

using namespace std;
namespace sdds {
	// this class extends Item, represent the Item with an expiry date
	class Perishable : public Item {
		Date expiryDate; // the expiry date
		char* Instruction; // instruction for the item
	public:
		Perishable();
		Perishable(Perishable& R);
		~Perishable();
		Perishable& operator=(Perishable& R);
		Date& expiry();
		ofstream& save(std::ofstream& ofstr)const;
		ifstream& load(std::ifstream& ifstr);
		ostream& display(std::ostream& ostr);
		istream& read(std::istream& istr);
	};
}
#endif // !PERISHABLE_H
