

// ------------------------------------------------polynomial.cpp-------------------------------------------------------
//Created by Jonathan Velazquez CSS343
// Creation 4/3/16
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of ths porgram is to create a polynomial class using linked list. It uses a dummy header at the position 0

#include <stdio.h>
#include "polynomial.h"


/* ------------------------------------polynomial Construstor-----------------------------------------------
 
 Description
 
 polynomial: New node is created with a coefficient of zero and a power of zero
 
 Preconditions: Driver must creat a empty Polynomial
 
 Postconditions: Poly nomial has been created, size 0, power 0, and coefficient 0.
 
 --------------------------------------------------------------------------------------------*/


Polynomial:: Polynomial(){
    head = new struct Term;                 // the front node is a dummy.
    size = 0;
    head->next = head;
    head->prev = head;
    head->power = 0;
    head->coeff = 0;
   // delete head;
    
}

/* ------------------------------------Copy Constructor-----------------------------------------------
 
 Description
 
 polynomial: the purpose of this constructor is to copy a polynomial without any memory leaks
 
 Preconditions: a polynomial opject should exist
 

 postconditions: a copy of the original will now be available with the same values as input p
 
 */

Polynomial:: Polynomial(const Polynomial &p){
    head = new struct Term; // creating a dummy header
    head->coeff=0;
    head->power=0;
    
    head->next=head;
    head->prev=head;
    size = 0;
    *this = p;
    
}

/* ------------------------------------polynomial destructor-----------------------------------------------
 
 Description
 
 polynomial: to delete a polynomial using a loop and null out the head to avoid memory leaks
 
 Preconditions:none
 
 postconditions: the polynomial will delete with a while loop unitl there is nothing in the list and NULL out the head.
 
 --------------------------------------------------------------------------------------------*/
Polynomial::~Polynomial(){
    Term *current = head;
    while(size > 0){ // walking throug the linked list unted
         remove(current->next);
    }
        current = NULL;
        delete current;				   // delete a dummy (at 0th).
    
 }

/* ------------------------------------degree-----------------------------------------------
 
 Description
 
 degree: will return the largest power
 
 preconditions: polynomial must be created to get a power of greater then 1
 

 postconditions: after executed if there is a polynomial the highest power will be returned or a -1
                 if there are no terms in the Polynomial
 
 --------------------------------------------------------------------------------------------*/

int Polynomial::degree( ) const{
   	if(size == 0) { //if Polynomial 0 terms return -1
        return -1;
    }
    return head->next->power;  //largets power will be returned
    
}
/* ------------------------------------coefficient-----------------------------------------------
 
 Description

 coefficient: returns the coefficient of the x^power term.

 preconditions: existing Polynomial
 
 
 postconditions:  return a double of the coef
 --------------------------------------------------------------------------------------------*/


double Polynomial::coefficient(const int power) const
{
    if(size == 0){  //if there are no Terms the coefficient is 0,
        return 0;
    }
    Term *p = head->next;
    for (int i = 1; p != NULL && p->power != power && i <= size; p = p->next, i++){}
    return ( p == NULL ) ? 0 :p->coeff;  // return 0 the coefficent was not found
}




/* ------------------------------------changeCoefficient-----------------------------------------------
 
 Description:
 
 changeCoefficient: changing coefficent at a given place
 
 preconditions: polynomial must exist
 postconditions: polynomial will be manipulated
 
 --------------------------------------------------------------------------------------------*/

bool Polynomial::changeCoefficient(const double newCoefficient, const int power){
    
    if(size == 0)  //when the size is zero we must  insert at the head
        return insert(head, newCoefficient, power);
    
    Term *temp = head->next; //create pointer to 1st term
    
    
    if(coefficient(power) == 0)  //if term of power doesn't exist insert it in proper position
        
    {
        if(degree() < power){  //if power greater than power of this Polynomial insert it at front
            
            
            return insert(head->next, newCoefficient, power);  //if insert successfull return true, else return false
        }
        else if(degree() > power)  // if Polynomial of larger degree than power, insert power in proper place
            
        {
            for(int i = 1; temp != NULL && temp->power > power && i <= size; temp = temp->next, i++){} //find proper place
            
            
            return insert(temp, newCoefficient, power);  //return true if insert is successfull, false otherwise
            
        }
        
        
        
        
    }
    
    else  //Polynomial has term of degree power
        
    {
        if(newCoefficient == 0) // if newCoefficient == 0 remove term of degree power
            
        {
            
            for(int i = 1; temp != NULL && temp->power != power && i <= size; temp = temp->next, i++){}  //find term with power
            
            if(temp->power == power)
                
                return remove(temp); /// calling remove to remove the Polynomial where it is located
        }
        
        else  //change coefficient of term of degree power
            
        {
            
            for(int i = 1; temp != NULL && temp->power != power && i <= size; i++, temp = temp->next){}
            
            if(temp->power == power)
                
                temp->coeff = newCoefficient;
            
        }
    }
    
    temp = NULL; //clearing out temp so no memory leaks occur
    
    return true; //if the operation is successfull
}
// Arithmetic operators
/* ------------------------------------Operator+-----------------------------------------------
 
 Description
 
 Operator+: two polynomials will be added together
 preconditions: two polynomials must exist
 
 postconditions: summed up polynomial will be returned
 
 --------------------------------------------------------------------------------------------*/
Polynomial Polynomial::operator+( const Polynomial& p ) const{
    
    Polynomial retVal;  //create new Polynomial to hold sum and return
    Term* thisPointer = head->next;  //create pointer to first term of this
    Term* pPtr = p.head->next;  //create pointer to first term of p
    
    
    int thisSize = size;    // get this.size
    int pSize = p.size;  // get p.size
    int thisSt = 1;  //starting index of this
    int pStart = 1;  //starting index of p
    Term* current = retVal.head;  //create pointer to new Polynomial's head
    
    for( ; (thisSt <= thisSize) && (pStart <= pSize); current=current->next)  //iterate over this and p and new polynomial
    {
        if(thisPointer->power > pPtr->power)  //bigger term goes into new polynomial first
        {
            retVal.changeCoefficient(thisPointer->coeff, thisPointer->power);  //insert term into new polynomial
            thisPointer = thisPointer->next;  //increment pointer
            thisSt++;   //increment index
        }
        else if(thisPointer->power < pPtr->power)
        {
            retVal.changeCoefficient(pPtr->coeff, pPtr->power);
            pPtr = pPtr->next;  //increment pointer
            pStart++;  //increment index
        }
        else  //new coefficient based on sum of thisPointer and pPtr power term
        {
            double newCoeff = pPtr->coeff + thisPointer->coeff;
            if(newCoeff != 0)
                retVal.changeCoefficient( newCoeff, thisPointer->power);
            thisPointer = thisPointer->next;  //increment pointers
            pPtr = pPtr->next;
            thisSt++;  //increment index of this polynomial
            pStart++;//increments index of p polynomial
        }
    }
    while(thisSt <= thisSize)
    {
        thisSt++;
        retVal.changeCoefficient( thisPointer->coeff, thisPointer->power);
        thisPointer = thisPointer->next;
        current = current->next;
    }
    while(pStart <= pSize)  //finish off pPtr side polynomial if neccessary
    {
        pStart++;
        retVal.changeCoefficient( pPtr->coeff, pPtr->power);
        pPtr = pPtr->next;
        current = current->next;
    }
    thisPointer = NULL;
    current = NULL;
    pPtr = NULL;
    return retVal;
    
}
/* ------------------------------------ (Operator-) -----------------------------------------------
 
 Description
 
 operator-: overloading the operator- function with polynomial
 
 preconditions: two polynomials will be added together

 postconditions: diifference of two polynomials will be returned
 
 --------------------------------------------------------------------------------------------*/
Polynomial Polynomial::operator-(const Polynomial& p) const
{
    Polynomial sum; //create new Polynomial to hold sum and return
    Term* thisPointer = head->next;  //create pointer to first term of this
    Term* pPtr = p.head->next;  //create pointer to first term of p
    int thisSize = size;  // get this.size
    int pSize = p.size;  // get p.size
    int thisSt = 1;  //starting index of this
    int pStart = 1;  //starting index of p
    Term* current = sum.head; //create pointer to new Polynomial's head
    for( ; (thisSt <= thisSize) && (pStart <= pSize); current=current->next)  //iterate over this and p and new polynomial
    {
        if(thisPointer->power > pPtr->power)  //bigger term goes into new polynomial first
        {
            sum.changeCoefficient(thisPointer->coeff, thisPointer->power); //insert term into new polynomial
            thisPointer = thisPointer->next; //increment pointer
            thisSt++; //increment index
        }
        else if(thisPointer->power < pPtr->power)   //bigger term goes into new polynomial first
        {
            sum.changeCoefficient( -(pPtr->coeff), pPtr->power);
            pPtr = pPtr->next;  //increment pointer
            pStart++; //increment index
        }
        else   //new coefficient based on sum of thisPointer and pPtr power term
        {
            double newCoeff = thisPointer->coeff - pPtr->coeff;  //sum thisPointer and pPtr power term coefficients
            if(newCoeff != 0)
                sum.changeCoefficient(newCoeff, thisPointer->power);  // do not insert coefficients that == 0
            thisPointer = thisPointer->next;  //increment pointers
            pPtr = pPtr->next;
            thisSt++;  //increment index
            pStart++; //increment pindex
        }
    }
    while(thisSt <= thisSize)  //finish off this
    {
        thisSt++;
        sum.changeCoefficient( thisPointer->coeff, thisPointer->power);
        thisPointer = thisPointer->next;
        current = current->next;
    }
    while(pStart <= pSize)  //finish off pPtr
    {
        pStart++;
        sum.changeCoefficient( -(pPtr->coeff), pPtr->power);
        pPtr = pPtr->next;
        current = current->next;
    }
    
    //nulling out the pointers so we dont have any memory leaks!!!!!!!
    thisPointer = NULL;
    current = NULL;
    pPtr = NULL;
    return sum;
}


// Boolean comparison operators

/* ------------------------------------operator==-----------------------------------------------
 
 Description
 
 operator==:compares two Polynomials to see if
 
 preconditions:  two polynomials will be compared together
 postconditions: true or false will be returned
 
 --------------------------------------------------------------------------------------------*/
bool Polynomial::operator==(const Polynomial& p) const
{
    Term* other = p.head->next;  //get first term of p
    Term* current = head->next;  //get first term of this
    if(size != p.size)  //if sizes dont match then they cannot be equal
    {
        return false;
    }
    for (int i = 1; other != NULL && current != NULL && i <= size; other = other->next,
         current = current->next, i++ )  //iterate over both polynomials
    {
        if(current != NULL && other != NULL)
        {
            if(current->power != other->power)  //if powers of same index don't match return false
                return false;
            if(current->coeff != other->coeff) //if coefficients of same index don't match return false
                return false;
            
        }
    }
    other = NULL;
    current = NULL;
    delete other;
    delete current;
    return true;  //all indexs match
}
/* ------------------------------------Operator!=-----------------------------------------------
 
 Description
 
 Operator!=: will check if two Polynomials are not equal
 preconditions:  two polynomials will be added together
 

 postconditions: true or false will be returned

 
 --------------------------------------------------------------------------------------------*/
bool Polynomial::operator!=( const Polynomial& p ) const
{
    
    return !(*this == p);  //if this == p return false, else true
}

// Assignment operators
 
 /* ------------------------------------operator=-----------------------------------------------
 
 Description
 
 operator=: will assign two one polynomial to the other
 preconditions: two polynomials must exist
  
 postconditions: the assigned polynomail will be returned
 
 --------------------------------------------------------------------------------------------*/

Polynomial& Polynomial::operator=(const Polynomial& p)
{
 
        while(size > 0)         //removing before copying over the terms
            remove(head->next);
   
       int index;
        
        Term* temp= p.head; //pointing the the first term position
        
        temp = temp->next; //moving temp to first position
        
        for ( index = 1; index <= p.size; //staring index at one because temp is pointing to position 1;
             
             temp = temp->next, index++ )  //add all elements of p to this
            
            changeCoefficient(temp->coeff, temp->power); // coping over the coefficent to this
        
        
    temp = NULL; //nulling out this so it wont
    delete temp;
    return *this;
}

/*------------------------------------operator+=-----------------------------------------------
 
 Description
 
 operator+=: this polynomail will equal this + p
 preconditions: two polynomail must exist
 postconditions: this polynomail will be returend once it is assigned
 
 --------------------------------------------------------------------------------------------*/


 Polynomial& Polynomial::operator+=( const Polynomial& p ){

     *this = *this + p; //using the operator + to add and return the value
     return *this;
}

/*------------------------------------ operator-= -----------------------------------------------
 
 Description
 
 operator-=: function to sort an array of integers
 preconditions:two polynomail must exist
 postconditions: this= this -p will be returned
 
 --------------------------------------------------------------------------------------------*/

Polynomial& Polynomial::operator-=(const Polynomial& p)
{
    *this = *this - p;
    return *this;
    }

/* ------------------------------------operator<<-----------------------------------------------
 
 Description
 
 operator<< : // Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
 
 precondition: string or object must exist
 postconditions: the output will be stored in output
 
 --------------------------------------------------------------------------------------------*/
ostream& operator<<( ostream &output, const Polynomial& p ){
    
    Polynomial::Term* curr = p.head->next;
    
    for(int index = 1; index <= p.size && curr != NULL; curr = curr->next, index++)
        
    {
        if(index == 1)  //First term should not include a binary operator
            
        {
            
            if(curr->power == 0)  //If x is raised to the 0, x = 1, do output terms coefficient
                
                output << curr->coeff;
            
            else if(curr->coeff == 1)  //If term's coefficient is one do not display the coefficient
                
            {
                
                if(curr->power == 1)  //If x is raised to the first power, no superscript needed, do not output ^1
                    
                    output << "x";
                
                else if(curr->power > 1)   //Output in the form of x^n
                    
                    output << "x^" << curr->power;
                
            }
            
            else if(curr->coeff > 1)  // Terms coefficient greater than 1
                
            {
                
                if(curr->power == 1)  //power == 1
                    
                    output << curr->coeff << "x"; //output x
                
                else if(curr->power > 1) //power greater than 1
                    
                    output << curr->coeff << "x^" << curr->power;  //output in the form of ax^n
                
            }
            
            else if(curr->coeff < 0)  //coefficient is negative
                
            {
                
                if(curr->coeff == -1){
                    
                    if(curr->power == 1)
                        
                        output << "-x";  //output -x
                    
                    else if(curr->power > 1)
                        
                        output << "-x^" << curr->power;  //output in form -x^n
                    
                }
                
                else if(curr->coeff < -1)
                    
                {
                    
                    output << curr->coeff << "x^" << curr->power;  //output in form of -ax^n
                    
                }
            }
        }
        
        else if(index != 1)  //must add a + or - before each term
            
        {
            if(curr->coeff < 0)  // add a - before each term
            {
                if(curr->power == 0)
                    output << " - " << -(curr->coeff);
                else if(curr->coeff == -1)
                {
                    if(curr->power == 1)
                        output << " - " << "x";
                    else if(curr->power > 1)
                        output << " - " << "x^" << curr->power;
                }
                else if(curr->coeff < -1)
                {
                    if(curr->power == 1)
                        output << " - " << -(curr->coeff) << "x";
                    else if(curr->power > 0)
                        output << " - " << -(curr->coeff) << "x^" << curr->power;
                }
            }
            else if(curr->power == 0)  //add a + before each term
                output << " + " << curr->coeff;
            else if(curr->coeff == 1)
            {
                if(curr->power == 1)
                    output << " + x";
                else if(curr->power > 1)
                    output << " + x^" << curr->power;
            }
            else if(curr->coeff > 1)
            {
                if(curr->power == 1)
                    output << " + " << curr->coeff << "x";
                else if(curr->power > 1)
                    output << " + " << curr->coeff << "x^" << curr->power;
            }
        }
    }
    
    return output << ", THE SIZE = "<<p.size;
}

// Constructor: the default is a 0-degree polynomial with 0.0 coefficient

/* ------------------------------------insert-----------------------------------------------
 
 Description
 
 insert: a polynomial will be manipulated
 
 preconditions: a polynomail must be created be fore running insert
 postconditions: polynomail will manipuatated to insert a term
 
 --------------------------------------------------------------------------------------------*/

bool Polynomial::insert(Term* prev, const double newCoefficient, const int power)
{
    if(prev == NULL)//Insert will fails
        return false;
    
    Term* insert = new Term;  //create new Term to insert
    insert->coeff = newCoefficient;
    

    insert->power = power;
    //checking to see if the power is a negative number
    if(power < 0)
    {
        cout << "You cannot insert a negative power" << endl;
        
       return false; //failed to insert
    }
    
    // insert before prev
    if(prev == head && size == 0)
    {
        //this term will be inserted in between the dummy head and the first term
        
        insert->next = head->next;
        
        head->next->prev = insert;
        
        head->next = insert;
        
        insert->prev = head;
    }
    
    else if(size > 0 && prev == head)
    {
        //insert will happen after the last term
        insert->prev = head->prev;
        insert->next = head;
        head->prev->next = insert;
        head->prev = insert;
    }
    else
    {
       
        prev->prev->next = insert;
        insert->prev = prev->prev;
        insert->next = prev;
        prev->prev = insert;
    }
    size++; //increment size
    insert = NULL;
    delete insert;
    return true;
}

/* ------------------------------------remove-----------------------------------------------
 
 Description
 
 remove: function to remove a coefficent and the power from the linked list
 
 preconditions: a polynomail must be created before running remove
 postconditions: a term will be removed
 
 --------------------------------------------------------------------------------------------*/
bool Polynomial::remove(Term* pos)
{

    if ( pos->prev != NULL )
        
        pos->prev->next = pos->next; // walking though and moving over the pointer
    if ( pos->next != NULL )
        pos->next->prev = pos->prev;
    delete pos;            // deallocate
    pos = NULL;
    size--;
    //delete pos;
    return true;
}


