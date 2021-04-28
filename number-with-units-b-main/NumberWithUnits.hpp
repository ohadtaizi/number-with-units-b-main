
#include <fstream>
#include <string>
#include <map>
#pragma once
using namespace std;

namespace ariel{



class NumberWithUnits{
    private:    
      double number;
       string unit;
         
    public:
        ~NumberWithUnits(){}
   
   NumberWithUnits(double num,string uni);
   

            friend int conversion(const NumberWithUnits& num1, const NumberWithUnits& num2);
        static void read_units(ifstream &units_file);
        friend NumberWithUnits operator+(const NumberWithUnits&  num1,  const NumberWithUnits&  num2); 

        friend NumberWithUnits operator+(const NumberWithUnits &a);
         friend NumberWithUnits &operator++(NumberWithUnits &a); 

        friend NumberWithUnits operator++(NumberWithUnits &a, int);

        friend NumberWithUnits &operator--(NumberWithUnits &a); 

        friend NumberWithUnits operator--(NumberWithUnits &a, int);  
        friend NumberWithUnits operator-(const NumberWithUnits& num1, const NumberWithUnits& num2); 
        friend NumberWithUnits operator-(const NumberWithUnits& num);
         NumberWithUnits& operator+=(const NumberWithUnits &num2);    
         NumberWithUnits& operator-=( const NumberWithUnits& num2);
        friend NumberWithUnits operator*( const NumberWithUnits& a, const double number);
         friend NumberWithUnits operator*(const NumberWithUnits &a,const NumberWithUnits &b);
        friend NumberWithUnits operator*(const double number,const NumberWithUnits& a);
        friend bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend ostream& operator << (ostream& s, const NumberWithUnits &a);
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &a);

};



}