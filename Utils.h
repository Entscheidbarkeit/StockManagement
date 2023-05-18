/*
this header files contains the utilities that we used for the whole application
*/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
using namespace std;
namespace sdds {
    // here we define a default date for test mode
   const int sdds_testYear = 2022;
   const int sdds_testMon = 03;
   const int sdds_testDay = 31;
   class Utils {
      bool m_testMode = false; // test mode is set when my implementation for functionality of date was imcomplete
   public:
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);
      void alocpy(char*& destination, const char* source);
      int getInt(const char* prompt = nullptr);
      int getInt(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
      double getDouble(double min, double max);
      double getDouble();
      const char* Date();
      string deleteMem(string& L, char R);
   };
   extern Utils ut; // set a global variable so that we can manipulate test mode outside
}

#endif // !SDDS_UTILS_H
