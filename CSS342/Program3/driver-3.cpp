//
//  main.cpp
//  Assignmnet 3
//
//  Created by Jonathan Velazquez on 2/2/16.
//  Copyright © 2016 Jonathan Velazquez. All rights reserved.
//

#include "dragon.h"

#include <iostream>

using namespace std;


#include "dragon.h"
#include <iostream>
using namespace std;

int main( ) {
    // right dragon at level 10
    dragon dragon10( 80, 360, 0 );
    dragon10.rightCurve( 10, 6 );
    
    // right dragon at level 9
    dragon dragon9( 360, 360, 0 );
    dragon9.rightCurve( 9, 6 );
    
    // right dragon at level 8
    dragon dragon8( 560, 360, 0 );
    dragon8.rightCurve( 8, 6 );
    
    // right dragon at level 7
    dragon dragon7( 120, 500, 0 );
    dragon7.rightCurve( 7, 8 );
    
    // right dragon at level 6
    dragon dragon6( 240, 500, 0 );
    dragon6.rightCurve( 6, 8 );
    
    // right dragon at level 5
    dragon dragon5( 360, 500, 0 );
    dragon5.rightCurve( 5, 8 );
    
    // right dragon at level 4
    dragon dragon4( 480, 500, 0 );
    dragon4.rightCurve( 4, 8 );
    
    // right dragon at level 3
    dragon dragon3( 60, 700, 0 );
    dragon3.rightCurve( 3, 16 );
    
    // right dragon at level 2
    dragon dragon2( 240, 700, 0 );
    dragon2.rightCurve( 2, 16 );
    

    // right dragon at level 1
    dragon dragon1( 420, 700, 0 );
    dragon1.rightCurve( 1, 16 );
    
}