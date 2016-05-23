// Author:  Jonathan Velazquez
// Date:    1/20/2016
// Purpose: To demonstrate a well-defined C++ class

#ifndef complex_H
#define complex_H

#include <iostream>
using namespace std;

class complex {
    
    // overloaded <<: prints "DIVIDE BY ZERO ERROR!!!" if denominator is zero,
    // prints whole numbers without denominator (as ints), otherwise uses '/'
    friend ostream& operator<<(ostream&, const complex&);
    
    // overloaded >>: takes 2 ints as numerator and denominator, does no
    // error checking, standard C casting between doubles, char, etc occurs
    friend istream& operator>>(istream&, complex&);
    
public:
    //This is the defualt constructor with two doubles initiated as zero's as the starting point
    complex(double real = 0.0, double imag = 0.0);
    
    friend complex operator+ (const complex &a, const complex &b);
    friend complex operator- (const complex &a, const complex &b);
    friend complex operator* (const complex &a, const complex &b);
    friend complex operator/ (const complex &a, const complex &b);
    
    // These two function will be used to get the real and imaginary number from the private section
    
    double getReal();
    double getImaginary();
    
    //Here are  incorporated the comparison operators using arithmetic operators
    
    bool operator==(const complex &) const;      // is the object == the input
    bool operator!=(const complex &) const;      // is the object != the input
    
    //Here is the plus equals operator spedified
    
    complex& operator+=(const complex &);       // current object += parameter
    complex& operator-=(const complex &);       // current object -= parameter
    complex& operator*=(const complex &);       // current object *= parameter
    complex& operator/=(const complex &);       // current object /= parameter
    
    
    complex conjugate();
    
    
private:
    
    
    double r;     //declaring real number as a private
    double i;     //declaring imaginary number as private
};

#endif  // complex_NUMBER




