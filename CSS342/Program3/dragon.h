//
//  dragon.hpp
//  Assignmnet 3
//
//  Created by Jonathan Velazquez on 2/2/16.
//  Copyright © 2016 Jonathan Velazquez. All rights reserved.
//

#ifndef dragon_h
#define dragon_h

#include "Turtle.h"
#include <iostream>
using namespace std;

class dragon : Turtle {
public:
    dragon( float initX=0.0, float initY=0.0, float initAngle=0.0 );
    void leftCurve( int l, float d );  //draw a level-l left curve with dist d
    void rightCurve( int l, float d ); //draw a level-l right curve with dist d
};
#endif
