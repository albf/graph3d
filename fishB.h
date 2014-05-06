#ifndef _fishB_
#define _fishB_

#include "renderable.h"
#include <iostream>
#include <stdio.h>
#include "math.h"

#define PI 3.14159
#define FOV_RADIUS 3           // Radius of field of view
#define FOV_ANGLE 110          // Radius of field of view angle

class fishB : public Renderable {
public:
    fishB();
    fishB(float posx, float posy, float posz,float velx, float vely, float velz, float colorA, float colorB, float colorC);
    virtual void draw();
    virtual void animate();
    void printXYZ(void);
    
    void setPos(float nx, float ny, float nz) {
        x=nx; y=ny; z=nz;
    }
    
    void setSpeed(float nx, float ny, float nz) {
        xSpeed=nx; ySpeed=ny; zSpeed=nz;
    }

    float x,y,z;                    // For Movement
    float xInc, yInc, zInc;         // Incremet of object
    float xSpeed, ySpeed, zSpeed;   // speed of object
    float colour[4];
    float xcp, ycp, zcp;            // Variables for cross-product
    int animation;
    int time;
private:             	
    float angle;  			// For Function animation
    float Autorun;			// For Movement Autorun
    
    float vectorDistance(float x, float y, float z);
    float getAngle(float x, float y, float z, float a, float b, float c);
    void getCrossProduct(float x, float y, float z, float a, float b, float c);
    float deg2rad( float deg ) { return deg * PI/ 180.0; }

    void printXYZInc(void) {
    std::cout << "xInc " << xInc << std::endl;
    std::cout << "yInc " << yInc << std::endl;
    std::cout << "zInc " << zInc << std::endl;
    std::cout << std::endl;
    }
};

#endif