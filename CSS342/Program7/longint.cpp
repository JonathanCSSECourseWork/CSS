#include "longint.h"

/* Three constructors are initialized here*/

LongInt:: LongInt( const string str)
{
    int i = 0;
    digits.clear(); // clearing digits
    if(str[0] == '-')
    {
        negative = true;
        i++;
    }
    else
    {
        negative = false;
    }
    while(i < str.length()){

        char d = str[i];
        int temp = d - '0';
        if (temp > -1 && temp < 10) //making sure temp is 0 < temp < 9
        {
            digits.addBack(str[i]);
        }
        i++;
    }
}
// copy Constructo
LongInt::LongInt (const LongInt & rhs)
{
    digits = rhs.digits;
    negative = rhs.negative;
}
//initializing to zero

LongInt::LongInt( ) {
    negative = 0;
}


//destructor is initialized uising the deque
LongInt::~LongInt( ) {
    digits.clear();
}


/* Operator +
 Considers the four different cases for addition.
 */
LongInt LongInt::operator+( const LongInt &rhs) const
{
    LongInt sumVal;
    string str = "";
    //Converts A + -B will now be A - B
    if(!negative && rhs.negative)
    {
        LongInt tempLHS, tempRHS;
        
        tempLHS.digits = digits;
        tempLHS.negative = false;
        
        tempRHS.digits = rhs.digits;
        tempRHS.negative = false;
        
        sumVal = tempLHS - tempRHS;
        return sumVal;
        
    }
    //Converting -A + B to become this  B - A
    else if(negative && !rhs.negative)
    {
        LongInt tempLHS, tempRHS;
        
        tempLHS.digits = digits;
        tempLHS.negative = false;
        
        tempRHS.digits = rhs.digits;
        tempRHS.negative = false;
        
        sumVal = tempRHS - tempLHS;
        return sumVal;                  //returning the sum
        
        
    }
    //-A + -B will now become -(A + B)
    else if(negative && rhs.negative)
    {
        LongInt temptempLHS,tempRHS; //declaring temp variable left and right
        
        temptempLHS.digits = digits;
        temptempLHS.negative = false;
        
        tempRHS.digits = rhs.digits;
        tempRHS.negative = false;
        
        sumVal = temptempLHS + tempRHS;
        sumVal.negative = true;
        return sumVal;
    }
    
    //adding a and b
    Deque<char> leftTempDig = digits;
    Deque<char> rightTempDig = rhs.digits;
    
    //make both left and right hand sides equal to each other for addition
    for(int i = rightTempDig.size(); i < leftTempDig.size(); i++)
    {
        rightTempDig.addFront('0');
    }
    for(int i = leftTempDig.size(); i < rightTempDig.size(); i++)
    {
        leftTempDig.addFront('0');
    }
    
    Deque<char> countNum = leftTempDig;
    
    int carry = 0;

    for(int i = 0; i < countNum.size(); i++)
    {
        int temp1 = leftTempDig.removeBack() - '0', temp2 = rightTempDig.removeBack() - '0';
        
        int sum = temp1 + temp2 + carry;
        carry = 0;
        if (sum >= 10)
        {
            carry = 1;
            sum -= 10;
        }
        str = string(1, (char)(((int)'0')+sum) ) + str;
        
    }
    
    if (carry > 0)
    {
        str = "1" + str;
    }
    
    Deque<char> sumDeque;
    for(int i = 0; i < str.length(); i++)
    {
        sumDeque.addBack(str[i]);
    }
    sumVal.digits = sumDeque;
    sumVal.negative = false;
    return sumVal;                                   //returning the sum value
    
}


LongInt LongInt::operator-( const LongInt &rhs) const
{
    LongInt tempVal;
    Deque<char> tempLeft;
    Deque<char> tempRight;
    // A - (-B)
    if(!negative && rhs.negative)
    {
        LongInt tempLHS, tempRHS;
        
        tempLHS.digits = digits;
        tempLHS.negative = false;
        
        tempRHS.digits = rhs.digits;
        tempRHS.negative = false;
        
        tempVal = tempLHS + tempRHS;
        return tempVal;
    }
    // COnverting -A - B => -(A + B)
    else if(negative && !rhs.negative)
    {
        LongInt tempLHS, tempRHS;
        
        tempLHS.digits = digits;
        tempLHS.negative = false;
        
        tempRHS.digits = rhs.digits;
        tempRHS.negative = false;
        
        tempVal = tempLHS + tempRHS;
        tempVal.negative = true;
        return tempVal;
    }
    //-A - (-B) => B - A
    else if(negative && rhs.negative)
    {
        LongInt tempLHS, tempRHS;
        
        tempLHS.digits = digits;
        tempLHS.negative = false;
        
        tempRHS.digits = rhs.digits;
        tempRHS.negative = false;
        
        if(tempLHS > rhs)
        {
            tempVal = tempLHS - tempRHS;
            tempVal.negative = true;
            return tempVal;
        }
        else if(tempLHS < rhs)
        {
            tempVal = tempRHS - tempLHS, tempVal.negative = false;
            return tempVal;
        }
        else
        {
            Deque<char> tempDeque;
            tempDeque.addBack('0');
            tempVal.digits = tempDeque,tempVal.negative = false;
            return tempVal;
        }
        
    }
    //Subtracting b from a
    else if(!negative && !rhs.negative)
    {
        LongInt tempLHS, tempRHS;
        
        //setting negative for both left and right
        tempLHS.digits = digits, tempLHS.negative = false, tempRHS.digits = rhs.digits, tempRHS.negative = false;
        
        if (tempLHS > rhs)
        {
            tempLeft = tempLHS.digits, tempRight = tempRHS.digits, tempVal.negative = false;
        }
        else if(tempLHS < rhs)
        {
            tempLeft = tempRHS.digits, tempRight = tempLHS.digits, tempVal.negative = true;
        }
        else
        {
            Deque<char> tempDeque;
            tempDeque.addBack('0');
            tempVal.digits = tempDeque;
            tempVal.negative = false;
            return tempVal;
        }
        
    }
    
    string str = "";
    
  
    
    Deque<char> countNum = tempLeft;
    int borrow = 0;
    //takes back integers and subtracts them. Less than 0, +10 and borrow=1
    for(int i = 0; i < countNum.size(); i++)
    {
        int temp1 = tempLeft.removeBack() - '0';
        int temp2 = tempRight.removeBack() - '0';
        
        int sum = temp1 - temp2 - borrow; // using borrow to subtract values
        borrow = 0;
        
        if(sum < 0)
        {
            sum = sum + 10;
            borrow = 1;
        }
        str = string(1, (char)(((int)'0')+sum) ) + str;
    }
    Deque<char> tempDeque;
    for(int i = 0;i < str.length(); i++)
    {
        tempDeque.addBack(str[i]);
    }
    tempVal.digits = tempDeque;
    return tempVal;
    
}
//Assignment operatator implemented

const LongInt& LongInt::operator=( const LongInt &rhs )
{
    //make this objects equal to rhs objects
    digits = rhs.digits;
    negative = rhs.negative;
    return *this;
}

//less then implemented here
bool LongInt::operator< (const LongInt & rhs) const
{
    LongInt temp;               //temp variable to hold left digits
    temp.digits = digits;
    temp.negative = negative;
    
    LongInt temp_rhs;           //temp right to hold the values of right
    temp_rhs.digits = rhs.digits;
    temp_rhs.negative = rhs.negative;
    bool retVal = true;
    if(temp.negative == true && rhs.negative == false)
    {
        return retVal;
    }
    else if(temp.negative == false && rhs.negative == true)
    {
        retVal=false;
        return retVal;
    }
    else
    {
        bool retVal2 = true;
        if(digits.size() != rhs.digits.size()) // when they do not match we will return false
        {
            if (digits.size() < rhs.digits.size())
            {
                retVal2 = true;
            }
            else if(digits.size() > rhs.digits.size())
            {
                retVal2 = false;
            }
            
            if (negative && rhs.negative) // both negative
            {
                return (!retVal2);
            }
            else
            {
                return retVal2;
            }
        }
        else //same size, check contents.
        {
            Deque<char> left = digits;
            Deque<char> right = rhs.digits;
            for (int i = 0; i < rhs.digits.size(); i++)
            {
                int ltemp = left.removeFront() - '0';
                int r = right.removeFront() - '0';
                
                if (ltemp > r)
                {
                    
                    if (!negative && !rhs.negative) //will check to seee if it is positive
                    {
                        
                        return false;
                    }
                    else
                    {
                        return true; //else it is negative
                    }
                }
            }
        }
        return (retVal2); // returing the value as true
    }
    
}

//Implement operator equal equla to see if they are actually equal
bool LongInt::operator==(const LongInt & rhs) const
{
    if(!negative && rhs.negative | negative && !rhs.negative) //signs not equal will return false automatically
    {
        return false;
    }
    else
    {
        if(digits.size() != rhs.digits.size())
        {
            return false;
        }
        else
        {
            bool retVal2 = true;
            Deque<char> left = digits;
            Deque<char> right = rhs.digits;
            for (int i = 0; i < rhs.digits.size(); i++)
            {
                char l = left.removeFront();
                char r = right.removeFront();
                if(l != r)
                {
                    retVal2 = false;
                }
            }
            return (retVal2);
        }
    }
}

/*Operator <= implementmented using == and <

 */
bool LongInt::operator<=( const LongInt & rhs ) const {
    return ( operator==(rhs) || operator<(rhs));
}

/*Operator > implemented using <=
 */
bool LongInt::operator> ( const LongInt & rhs ) const {
    return !(operator<=(rhs));
}

/*Operator >=
implemented uisng <
 */
bool LongInt::operator>=( const LongInt & rhs ) const {
    return (!operator<(rhs));
}

/*Operator !=
Implemented usin == as !
 */
bool LongInt::operator!=( const LongInt & rhs ) const {
    return !operator==(rhs);
    
}




/*Overriding instream*/

istream &operator>>( istream &in, LongInt &rhs)
{
    string input;
    
    in >> input; ///puting in the word from instret to word
    LongInt temp(input);
    rhs = temp; //seting the rhs to place holder
    return in;
}

//Operator <<
//overloading operator outstream
ostream &operator<<(ostream &out, const LongInt &rhs)
{
    string outLong;
    LongInt temp = rhs;
    bool val = false;

    for(int i = 0; i < rhs.digits.size(); i++)
    {
        
        int num = temp.digits.removeFront() - '0';
        if(num == 0 && val == false)
        {
            
        }
        
        else
        {
            val = true;
            outLong = outLong + string(1, (char)(((int)'0')+ num));
        }
        
    }
    
   //checking two conditions if zero or 1
    if(outLong.length() == 0) // if it equal to zero
    {
        out << "0";
        return out;
    }
    else if(outLong.length() == 1) //if it isqual to 1
    {
        if(outLong[0] == '0')
        {
            out << "0";
            return out;
        }
        else if(rhs.negative) //when rhs si negative we will add '-'
        {
            out << "-";
            out << outLong;
            return out;
        }
        else                //when rhs is positve
        {
            out << outLong;
            return out;
        }
    }
    else
    {
        if(rhs.negative)    //when rhs is negative we will add '-'
        {
            out << "-";
            out << outLong;
            return out;
        }
        else
        {
            out << outLong;
            return out;
        }
    }
    //out << outLong;
    return out;
}