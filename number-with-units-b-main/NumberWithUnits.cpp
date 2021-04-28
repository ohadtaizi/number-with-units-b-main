
 #include <iostream>
 #include <fstream>
 #include <sstream>
#include "NumberWithUnits.hpp"
#include <map>
#include <cstdlib>
using namespace std;

namespace ariel
{
    const double ep = 0.00001; 
    
    static map<string, map<string, double>> conversions;

    NumberWithUnits::NumberWithUnits(double num,string uni)
    {
        conversions.at(uni); 

        this->number = num;
        this->unit = uni;
    }
     double converter(double number, const string &source, const string &target){
     
        if (conversions[source].count(target) == 0)
         {
             throw "Error";
         } 
         if (source == target)
         {
             return number;
         }
         return number * conversions[source][target];
     }
    void NumberWithUnits::read_units(ifstream &file_name) 
    {
        double one = 0;
        double tow = 0;

        string ONEunit, TOWunit, EQ;

        while (file_name >> one >> ONEunit >> EQ >> tow >> TOWunit)
        {

            conversions[ONEunit][TOWunit] = tow;

            conversions[TOWunit][ONEunit] = one / tow;


            for (auto &current_unit : conversions[ONEunit])
            {
                double current_val = conversions[TOWunit][ONEunit] * current_unit.second;

                conversions[TOWunit][current_unit.first] = current_val;
                conversions[current_unit.first][TOWunit] = 1 / current_val;
            }
            for (auto &current_unit : conversions[TOWunit])
            {
                double current_val = conversions[ONEunit][TOWunit] * current_unit.second;

                conversions[ONEunit][current_unit.first] = current_val;
                conversions[current_unit.first][ONEunit] = 1 / current_val;
            }
        }
    }

     NumberWithUnits operator+(const NumberWithUnits &num)
    {
        NumberWithUnits t(+num.number,num.unit);

        return t;
    }

    NumberWithUnits operator+(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        double num3 = converter(num2.number, num2.unit, num1.unit);

        NumberWithUnits t(num3 + num1.number, num1.unit);

        return t;
    }

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &num)
    {
             double num3=converter(num.number,num.unit,this->unit);
         this->number+= num3;
        return *this;
    }

    

    NumberWithUnits operator-(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        double num3 = converter(num2.number, num2.unit, num1.unit);
        NumberWithUnits t(num1.number-num3, num1.unit);
        return t;
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &num)
    {
        double num3=converter(num.number,num.unit,this->unit);
         this->number-= num3;
        return *this;
    }

    bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
       return num1.number>converter(num2.number,num2.unit,num1.unit);
    }

    NumberWithUnits operator-(const NumberWithUnits &num)
    {
        NumberWithUnits t(-num.number,num.unit);
        return t;
    }


    
       bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return num1.number<converter(num2.number,num2.unit,num1.unit);
    }

    bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        double num3 = converter(num2.number,num2.unit,num1.unit);
        return num1.number>num3 || abs(num1.number-num3)<ep;
    }

  


    bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return abs(num1.number-converter(num2.number,num2.unit,num1.unit))<ep;
    }

    bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return num1.number!=converter(num2.number,num2.unit,num1.unit);
    }
   bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        double num3 = converter(num2.number,num2.unit,num1.unit);
        return num1.number<num3 || abs(num1.number-num3)<ep;
    }

    NumberWithUnits &operator++(NumberWithUnits &num1) 
    {   
        num1.number++;
        return num1;
    }
        NumberWithUnits operator--(NumberWithUnits &num, int)
    {
        NumberWithUnits t=num;
        num.number--;
        return t;
    }
    NumberWithUnits operator++(NumberWithUnits &num1, int)
    {
        NumberWithUnits t=num1;
        num1.number++;
        return t;
    }

    NumberWithUnits &operator--(NumberWithUnits &num)
    {
        num.number--;
        return num;
    }
   NumberWithUnits operator*(double num2,const NumberWithUnits &num1){ 
        return NumberWithUnits(num1.number*num2,num1.unit);
    }



    NumberWithUnits operator*(const NumberWithUnits &num1, double num2)
    {
        return NumberWithUnits(num1.number*num2, num1.unit);
    }


    NumberWithUnits operator*(const NumberWithUnits &num1,const NumberWithUnits &num2){
        double num3 = converter(num2.number,num1.unit,num2.unit);

        NumberWithUnits t(num1.number*num3, num1.unit);

        return t;
    }


    ostream &operator<<(ostream &s, const NumberWithUnits &a)
    {
        return s<<a.number<<"["<<a.unit<<"]";
    }


       istream& operator>>(istream& s, NumberWithUnits& a){
        char left=' ',right=' ';
        string temp=" ";
        double num = 0;
        s >> skipws >> num >> left >> temp;

        uint length = temp.length();
        char ch = temp.at(length - 1);
        if (ch != ']'){

            s >> right;
        }
        else{
            temp = temp.substr(0, length - 1);
        }
        if (conversions.count(temp) == 0)
        {
            throw invalid_argument("error");
        }
         a.unit = temp;
        a.number = num;
       
        return s;
    }
}