#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include<iomanip>
#include<cstring>
#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut; // create an instance for external use
   // setter for test mode
   void Utils::testMode(bool testmode) { 
      m_testMode = testmode;
   }
   // removes the character R from string L
   string Utils:: deleteMem(string& L,  char R) {
       string::iterator jb = L.begin();
       while (jb != L.end()) {
           if (*jb == R)
               jb = L.erase(jb);
           else
               jb++;
       }
       return L;
   }
   // get a data from default date or system date
   void Utils::getSystemDate(int* year, int* mon, int* day) { 
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   // returns the days in the given month and year
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      // the int constructor initialization for Feburary in leap year.
      //here we take the value of boolean into integer and only when all the expression is true(1), is the multiplication 1 else 0
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)); 
   }
   // a string copy for char pointer
   void Utils::alocpy(char*& destination, const char* source) {
       delete[] destination;
       if (source != nullptr) {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
       }
   }
   // a getInt to validate the user input. only numbers are accepted, else prompt the user to retry
   int Utils::getInt(const char* prompt) {
       if (prompt != nullptr) {
           cout << prompt << endl;
       }
       bool flag = false;
       bool flag2 = true;
       char ip[15];
       int i = 0;
       int length = 0;
       while (flag == false) {
           cin >> ip;
           length = strlen(ip);
           flag2 = true;
           for (i = 0;i < length;i++) {
               if (ip[i] < 48 || ip[i]>57) {
                   cout << "Invalid Integer, retry: ";
                   flag2 = false;
                   break;
               }
           }
           if (flag2 == true)
               flag = true;
       }
       return atoi(ip);
   }
   // this getInt validate the input as number in a certain range
   int Utils::getInt(int min, int max, const char* prompt, const char* errMes) {
       bool flag = false;
       bool flag2 = true;
       int ip = 0;
       while (flag == false) {
           ip = getInt(prompt);
           flag2 = true;
           if (ip<min || ip >max) {
               flag2 = false;
               if (errMes == nullptr) {
                   cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
               }
               else {
                   cout << errMes << ", retry: ";
               }
           }
           if (flag2 == true)
               flag = true;
       }
       return ip;
   }
   // validate the input in range of min and max
   double Utils:: getDouble(double min, double max) {
       bool flag = false;
       bool flag2 = true;
       double ip = 0;
       while (flag == false) {
           ip = getDouble();
           flag2 = true;
           if (ip<min || ip >max) {
               flag2 = false;
               cout << "Value out of range [" << setiosflags(ios::fixed) << setprecision(2) <<min << "<=val<=" << setiosflags(ios::fixed) << setprecision(2) << max << "]: ";
           }
       if (flag2 == true)
           flag = true;
       }
       return ip;
   }
   // validate the input as a double(number with a '.')
   double Utils::getDouble() {
       bool flag = false;
       bool flag2 = true;
       char ip[15];
       int i = 0;
       int length = 0;
       while (flag == false) {
           cin >> ip;
           length = strlen(ip);
           flag2 = true;
           for (i = 0;i < length;i++) {
               if ((ip[i] < 48 || ip[i]>57)&&ip[i]!='.') {
                   cout << "Invalid number, retry: ";
                   flag2 = false;
                   break;
               }
           }
           if (flag2 == true)
               flag = true;
       }
       return atof(ip);
   }
   // returs a string represtation of current time.
   const char* Utils:: Date() {
       time_t now = time(0);
       tm* ltm = localtime(&now);
       int cYear = 1900 + ltm->tm_year;
       int cMonth = 1 + ltm->tm_mon;
       int cDay = ltm->tm_mday;
       string rtn;
       rtn += cYear;
       rtn += '/';
       rtn += cMonth;
       rtn += '/';
       rtn += cDay;
       return (rtn.c_str());
   }
}