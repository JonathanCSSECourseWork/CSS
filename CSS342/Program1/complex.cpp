//Jonathan Velazquez


#include "complex.h"

complex::complex(double rr, double ii) : r(rr), i(ii)   //constructer
{
}


//--------------------------------- add --------------------------------------
// overloaded +: addition of 2 complex, current object and parameter
//

complex operator+ (const complex &a, const complex &b)
{
    complex sum;
    
    sum.r = a.r + b.r;  //adding to get the real number
    sum.i = a.i + b.i;  //adding to get the imaginary number
    
    return sum; //returning the sum
}

//------------------------------ subtract ------------------------------------
//overloading the -: differnce of 2 complex numbers

complex operator- (const complex &a, const complex &b)
{
    complex difference; //
    
    difference.r = a.r - b.r;  //
    difference.i = a.i - b.i;
    
    return difference; //returning the difference
}

//------------------------------ multiply ------------------------------------
//overloading the *: product of 2 complex number

complex operator* (const complex &a, const complex &b)
{
    complex product;
    
    product.r  = (a.r * b.r - a.i * b.i); //foiling out to figure out the real number
    
    product.i = (a.r * b.i + a.i * b.r); // foiling out to get the imaginary number
    
    
    return product;      // returning the product
}


//-------------------------------- divide ------------------------------------
//overloading the /: quotient of 2 complex number

complex operator/ (const complex &a, const complex &b)
{
    complex quotient;
    if(b != 0){
        quotient.r = (a.r * b.r + a.i * b.i) / (b.r * b.r + b.i * b.i); //calculation to produce the division
        quotient.i = (a.i * b.r - a.r * b.i) / (b.r * b.r + b.i * b.i);
        return quotient;
    }else{
        cout <<" Cant divide by zero!";  // cant divide by zero error
        
    }
    return quotient; //returing the quotient of the two complex
    
    
}
//------------------------------getReal------------------------------------
// The getReal will return the value that is held in the real

double complex::getReal()
{
    return r;          // the real number is returned as an double
    
}

//------------------------------getImaginary------------------------------------
// The getImaginary will return the value that is held in the private imgainary
double complex::getImaginary()
{
    return i;       // the imaginary is retured as an double
    
}


//----------------------------------------------------------------------------
// operator==
// overloaded == checking to see if they are equal

bool complex::operator==(const complex &right) const{
    
    if ((r == right.r) && (i == right.i)) // comparing real and imaginary
        return true;  // returns true if it does
    else
        return false;  // returns false if it doesnt
    
}
//-----------------------------operator !=-------------------------------------
// overloaded != checking to see if they are not equal
bool complex::operator!=(const complex &right) const{
    
    if ((r != right.r) && (i != right.i)) // checks to see if they are not equal by comparing real and imaginary numbers of
        return true;  // returns
    else
        return false;
    
    
}
//----------------------------Assignment += Class-----------------------------------

// overloaded += current object = current object + parameter


complex& complex::operator+=(const complex& a) {
    
    r = r + a.r; //algorithm to compute
    i = a.i +i ;
    
    
    return *this;
}

//----------------------------Assignment -= Class-----------------------------------

// overloaded -= current object = current object - parameter

complex& complex::operator-=(const complex& c) {
    r = r - c.r;
    i = i - c.i;
    return *this;
}

//----------------------------Assignment *= Class-----------------------------------

// overloaded *= current object = current object * parameter
complex& complex::operator*=(const complex& c) {
    
    r = r * c.r;
    i = i * c.i;
    return *this;
}


//----------------------------Assignment /= Class-----------------------------------

// overloaded /= current object = current object / parameter

complex& complex::operator/=(const complex& c) {
    this->r = this->r/c.r;
    
    this->i = this->i/c.i;
    
    
    return *this;   // reference is returned
}


complex complex::conjugate()
{
    complex temp;   // temp holds the new value that will be returned
    temp.r= r;
    temp.i = i * -1; // multiplying by -1 to get the congugate
    return temp;   // temp is returnd
}

//----------------------------------------------------------------------------
// operator<<



ostream& operator<< (ostream &out, const complex &b) {
    
    bool rPrinted = false;
    
    if (b.r != 0 || (b.r == 0 && b.i == 0)) { // check if real and imaginary are zero
        out << b.r;                     // prints out the real number
        rPrinted = true;                // sets it to true
    }
    
    if (b.i > 0) {                     // checks to see if imaginary is greater then zero
        if (rPrinted) {
            out << "+";                //prints out the plus between the two number
        }
        if (b.i != 1) {                //checks to see if the the imaginary number is not one
            out << b.i;
        }
        out << "i";                    // prints out the i before the imaginary number
    } else if (b.i < 0) {
        if (b.i == -1) {               // checks to see if the imaginary number is -1
            out << "-";                // prints out the negative infront of the imaginary number
        } else {
            out << b.i;                //prints out the imaginary number as a negative
        }
        out << "i";                    //prints out the i for the imaginary number
    }
    
    return out;                        //returns the output
}



//----------------------------------------------------------------------------
// operator>>
// overloaded >>: takes 2 ints as numerator and denominator, does no
//    error checking, standard C casting between doubles, char, etc occurs

istream& operator>>(istream &input, complex &a) {
    input >> a.r >> a.i;
    
    
    return input;
    
}


