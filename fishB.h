#ifndef _fishB_
#define _fishB_

#include "renderable.h"
#include <iostream>
#include <stdio.h>
#define PI 3.14159
#define FOV_RADIUS 3           // Radius of field of view
#define FOV_ANGLE 110          // Radius of field of view angle

class fishB : public Renderable {
public:
    fishB();
    virtual void draw();
    void printXYZ(void);

    float x,y,z;            // For Movement
    float xInc, yInc, zInc;   // speed of object
    float colour[4];
    float xcp, ycp, zcp;        // Variables for cross-product

private:             	
    float angle;  			// For Function animation
    float Autorun;			// For Movement Autorun
    
    float vectorDistance(float x, float y, float z);
    float getAngle(float x, float y, float z, float a, float b, float c);
    void getCrossProduct(float x, float y, float z, float a, float b, float c);
};

#endif