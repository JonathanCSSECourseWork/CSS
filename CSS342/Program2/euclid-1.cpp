//  Uclid.cpp
//  Program2
//
//  Created by Jonathan Velazquez on 1/26/16.
//  Copyright © 2016 Jonathan Velazquez. All rights reserved.
//

#include <iostream>

#include <sys/time.h>
#include <stdio.h>
using namespace std;
/* this function will calculate the greatest common denominator of two integer values. The way we find the gcd is by usinghee uclidean algorithm. We repeat the process of long division until the remainder is zero. The gcd is return from the function. The count is passed through as a reference so we can keep track of how many modules operation it took
 */
int gcd(int b, int a, int &count) { //gcd with to variable that are passed by value
    
    int temp = 0;   //used to hold a temp value
    //int count = 0;  //used to keep th count for the module operations used
    
    while(b!=0){    //once b hits zero the gcd has been found
        
        temp = b;   //used to hold the spot of b so can be passed to a
        b = a%b;    //finding the remainder
        
        a = temp;   //replacing a with the value of b
        count++;    //module operations
        
    }
    return a; //returns count of the modules used
}



int main(){
    
    

    int input = 0;// will be holding the value of the input balue of "n"
    
    int start = 8;          //staring with 8 as the first threshold
    int count = 0;          //count is declared in the main then passed through
    int GCD = 0;            //holds the value of GCD
    
    int currentHighest =0;  //wil hold the current highest module operation of the gcd
    
    int currentModule = 0; // holds the value of the current module operator count
    
    int highestA = 0; // will hold temporary highest value of a
    int highestB = 0; // will hold temporary highest value of b
    
    cout << "Enter n: " ;       // will display to the console
    cin >> input;  //sets the value types by the keyboard as input
    
    struct timeval tim;
    gettimeofday(&tim, NULL);
    double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
    
    while(start <= input){                                  // loop that lets you start from 8 to input value
        
        for(int a = 1; a <= start; a++){                    //loop to go through all the possible variation of a
            
            for(int b = a+1; b <= start; b++){          //loop to go through all the possible variations of b
            
                
                GCD = gcd(a, b, count);              //calls gcd to find the greatest highest common denominator
                currentModule = count;
                count = 0;
                
                if(currentModule > currentHighest){ //checkts to see if the current count is higher then the previously stored highest value
                    
                    currentHighest = currentModule; //calls the gcd to test two integers
                    
                    highestA= a; //hodls the value of  "a" with the highest modules operator
                    
                    highestB = b; //holds the value of "b" with the highest modules operator
                    
                }
                
            }
        
        }
        
        
        cout<< "i = " << start << "; gcd ("<< highestA << "," << highestB <<         //prints out the a and b value and amout of module operations it
        ") = "<< gcd(highestB,highestA, count)<< " took " << currentHighest << " module operations " << endl;
        count = 0;
        start++; //increments the threshold by one se can now check on number up
    }
    
 gettimeofday(&tim, NULL);
    
    double t2=tim.tv_sec+(tim.tv_usec/1000000.0);

    
     printf("%.6lf microseconds elapsed \n", (t2-t1)*1000000);
    
    return 0; //ends the program by returning zero
    
}




