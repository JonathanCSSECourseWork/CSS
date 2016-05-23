//
//  mergesortImproved.cpp
//  Program 4
//
//  Created by Jonathan Velazquez on 2/23/16.
//  Copyright © 2016 Jonathan Velazquez. All rights reserved.
//

#include <vector>
#include <math.h> // may need to use pow( )
using namespace std;

template <class Comparable>

//Function that will swap the left and the right of the aray
void swap(vector<Comparable> &a, vector<Comparable> &b){
    vector<Comparable> tempHolder;
    
    tempHolder = a; //Holds a temp holder to do the swap
    a = b;          //left and right side will switch
    b = tempHolder; //right(b) will now take the values of a which are held in the tempHolder
}

//This function will place the remaining numbers into the array
template <class Comparable>
void placeInArray(vector<Comparable> &a, vector<Comparable> &b, int &right, int &end, int &left, int &leftend, int &k){
    vector<Comparable> tempHolder;
    
    while (right < end) //populating the right side of the array
    {
        b[k] = a[right];
        right++;
        k++;q
    }
    while (left <leftend) //populaintg the left end of the array
    {
        b[k] = a[left];
        left++;
        k++;              //
    }
}
/*
 * The improved iterative mergesort() function
 * @param vector<Comparable>
 *
 */
template <class Comparable>
void mergesortImproved(vector<Comparable> &a) {
    
    //this method takes one parameter to be sorted
    int size = a.size(); //sets the variable size to the size of the array
    vector<Comparable> b(size);  // this is only one temporary array.
    
    
    //pointers to the array so they can swap without copying array
    
    for (int i = 1; i <= size ; i *= 2) //for loop that goes from one to zi-1, and increments i*=2 because of the split
    {
        //loop through each set of comparators
        for(int start = 0; start <= size; start += 2 * i) // for loop geos from 0 to size-1, increments start as start +=2*1 because it splits
        {
            //initializes the middle to the staring postion of zero plus the value of i
            int middle = start + i;
            
            int end =  int(fmin(middle + i, size)); //sets end to the value min value of the right end
            
            int leftend = int(fmin(middle, size));//sets leftend to the value min vlue of the left end
            
            int left = start, right = middle, k = start; //sets left the start and right to middle and k will be the staring value to go through
            
            //compares two sets of numbers and puts lowest in other array
            while (left < leftend  && right < end )
            {
                //This checks if the right side is >=size
                if ( right >= size || a[left] <= a[right])
                {
                    b[k] = a[left]; //if it is then a is set to b(k)
                    left++;// left increases by one
                }
                else
                {
                    b[k] = a[right]; ///it set the spot to the new spot in the second half
                    right++; //moves over the right side
                }
                k++;
            }
            
            //calss this function to place remaining values in array
            placeInArray(a, b, right, end, left, leftend, k);
            
        }
        
        //swap function to switch a-b >>> b-a
        swap(a,b);
        
    }
}




