//
//  dragon.cpp
//  Assignmnet 3
//
//  Created by Jonathan Velazquez on 2/2/16.
//  Copyright © 2016 Jonathan Velazquez. All rights reserved.
//

#include "dragon.h"

//------------------------- Dragon ----------------------------
dragon::dragon( float initX, float initY, float initAngle )
: Turtle( initX, initY, initAngle ) {
}

//------------------------------ leftCurve ----------------------------------
// draw a level-l left curve with dist d
//it will use recursion to draw out a pattern by calling both leftCurve and rightCurve
void dragon::leftCurve(int level, float d) {
    if (level > 0) {
        leftCurve(level - 1, d);    //calls the left cure as recursively
        turn(90);                   //turns the line 90 degrees to the right
        rightCurve(level - 1, d);   //calls the right curve recursively
        turn(90);                   //turns the line 90 degrees to the right
    }
    else
        draw(d); //once it is less then zero it will call the function draw
}

//------------------------------ rightCurve ---------------------------------
// draw a level-n right curve with distance d
//it will use recursion to draw out a pattern by calling both leftCurve and rightCurve
void dragon::rightCurve(int level, float d) {
    if (level > 0) {                //checking to see if it greater then zero
        turn(-90);                 //turns the line 90 degrees to the left from the start
        leftCurve(level - 1, d);    //calls the left curve recursively
        turn(-90);                  //turns the line 90 degrees to the left from the previous line
        rightCurve(level - 1, d);
    }
    else
        draw(d); //once it is less then zero it will call the function draw
}
