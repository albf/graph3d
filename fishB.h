#ifndef _fishB_
#define _fishB_

#include "renderable.h"
#include <iostream>
#include <stdio.h>
#define PI 3.14159

class fishB : public Renderable {
public:
    fishB();
    virtual void draw();
    void printXYZ(void);

    GLfloat x,y,z;            // For Movement
    GLfloat xInc, yInc, zInc;   // speed of object
    float colour[4];

private:             	
    float angle;  			// For Function animation
    float Autorun;			// For Movement Autorun

};

#endif