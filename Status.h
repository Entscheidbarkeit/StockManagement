#ifndef STATUS_H
#define STATUS_H


using namespace std;
namespace sdds {
	// this class represent the validation of every classes
	class Status {
		char* description; // description of status
		int statusCode; // status code 

	public:
		Status(const char* i_description = nullptr);
		Status& operator = (const char* i_description);
		Status& operator = (int i_code);
		operator const char*() const;
		operator int() const;
		operator bool() const;
		void clear();
		friend ostream& operator<< (ostream& os, const Status& R);
	};
}

#endif // !STATUS_H