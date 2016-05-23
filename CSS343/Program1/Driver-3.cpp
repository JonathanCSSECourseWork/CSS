//
//  Driver.cpp
//  Program7
//
//  Created by Jonathan Velazquez on 4/2/16.
//  Copyright © 2016 Jonathan Velazquez. All rights reserved.
//
#include <iostream>
using namespace std;

#include "polynomial.h"

int main( )

{
    //testing the defualt constructor
    Polynomial p1;
    Polynomial p2;
    Polynomial p10;
    
    
    //test for change Coefficicient
    p1.changeCoefficient(2,3);
    p1.changeCoefficient(2,5);
    p1.changeCoefficient(3,4);
    p1.changeCoefficient(4,7);
    p2.changeCoefficient(2,2);
    p2.changeCoefficient(3,3);
    p10=p1;
    
    cout<<"\nTesting out changeCoefficient with 4 inputs"<<endl;
    cout<<"p1 = "<<p1<<endl;
    
    cout<<"\nTesting out changeCoefficient with 0^3"<<endl;
    cout<<"p10 before change "<<p10<<endl;
    p10.changeCoefficient(0,3);
    
    cout<<"p10 = "<<p10<<endl;

    //testing out copy constructor
    cout<<"\nTesting out copy constructor"<<endl;
    Polynomial p3 =Polynomial(p1);
    cout<<"p3 = "<<p3<<endl;
    
    //test for the destructor
    p3.~Polynomial();
    cout<<"\nTest out destructor\n"<<endl;
    
    //test for the degree()
    cout<<"\nTest out highest degree() of p1"<<endl;
    cout<<"p1 = "<<p1<<endl;
    cout<<"higest power of p1 = "<<p1.degree()<<endl;
    
    //test for the coefficient of a given power
    cout<<"\nTest out coefficnet of power of 3 in p1"<<endl;
    cout<<"p1 = "<<p1<<endl;
    cout<<"COEFFICIENT of power 3 is "<<p1.coefficient(3)<<endl;
    
    //test for change coefficient
    cout<<"\nTest for changeCoefficient"<<endl;
    p1.changeCoefficient(0,5);
    cout<<p1<<endl;
    
    //Test Arithmetic operators + and -
    cout<<"\nTest for operator+"<<endl;
    cout<<"p1 = " <<p1<<endl;
    cout<<"p2 = " <<p2<<endl;
    cout<<"p1+p2 = " <<p1+p2<<endl;
    
    cout<<"\nTest for operator-"<<endl;
    cout<<"p1 = " <<p1<<endl;
    cout<<"p2 = " <<p2<<endl;
    cout<<"p1-p2 = " <<p1-p2<<endl;
    
    // Boolean comparison operators == and !=
    cout<<"\nTest for operator=="<<endl;
    Polynomial p4 = Polynomial(p1);
    cout<<"p1 = " <<p1<<endl;
    cout<<"p4 = " <<p4<<endl;
    cout<<"p2 = " <<p2<<endl;
    bool a = p1==p4;
    bool b = p1==p2;
    bool c = p1!=p4;
    bool d = p1!=p2;
    
    cout<<"\nIs p1 and p4 equal? "<<a<<endl;
    cout<<"Is p1 and p2 equal? "<<b<<endl;
    
    cout<<"\nTest for operator!="<<endl;
    
    cout<<"\nIs p1 != to p4? "<<c<<endl;
    cout<<"Is p1 != p2 equal? "<<d<<endl;
    
    //Test Assignment operators ==, += and -=
    cout<<"\nTest for operator="<<endl;
    Polynomial p7 =Polynomial(p1);
    Polynomial p8 = Polynomial(p2);
    
    cout<<"p7 = " <<p7<<endl;
    cout<<"p8 = " <<p8<<endl;
    p7=p8;
    cout<<"(p7=p8) p7 now equals " <<p7<<endl;
    
    cout<<"\nTest for operator+="<<endl;
    cout<<"p1 = " <<p1<<endl;
    cout<<"p2 = " <<p2<<endl;
    p1+=p2;
    cout<<"(p1+=p2) p1 now equals" <<p1<<endl;
    
    cout<<"\nTest for operator-="<<endl;
    cout<<"p1 = " <<p1<<endl;
    cout<<"p2 = " <<p2<<endl;
    p1-=p2;
    cout<<"(p1-=p2) p1 now equals " <<p1<<endl;
    
}
