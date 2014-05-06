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
    
    void setSpeed(float nx, float ny, float nz) {
        xSpeed=nx; ySpeed=ny; zSpeed=nz;
    }

    float xSpeed, ySpeed, zSpeed;   // speed of object
    float colour[4];
    int animation;
    int time;
private:             	
    float angle;  			// For Function animation
    float Autorun;			// For Movement Autorun
};

#endif