#ifndef MENU_H
#define MENU_H


using namespace std;
namespace sdds {
	// a Menu for user interface
	class Menu {
		// the list to be printed
		char* list;
		// the options given
		unsigned int options;
	public:
		Menu(const char* list, unsigned int opt);
		void clear();
		int run();
	};
}

#endif // !MENU_H
