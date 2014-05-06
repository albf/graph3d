#ifndef _crab_
#define _crab_

#include "renderable.h"
#include <iostream>
#include <stdio.h>
#include "math.h"
#include <iostream>

class crab : public Renderable {
public:
    crab();
    crab(float posx, float posz,float velx, float velz);
    virtual void draw();
    virtual void animate();
    void printXYZ(void);

    void setPos(float nx, float ny, float nz) {
        x=nx; y=ny; z=nz;
    }
    
    void setSpeed(float nx, float ny, float nz) {
        xInc=nx; yInc=ny; zInc=nz;
    }

    float x, y, z; // For Movement
    float xInc, yInc, zInc; // speed of object
    float xcp, ycp, zcp; // Variables for cross-product

    static GLfloat material[4];
    static GLfloat shininess;
    GLUquadricObj *quadric; // quadric object for all renderables

private:

    float vectorDistance(float x, float y, float z);
    float getAngle(float x, float y, float z, float a, float b, float c);
    void getCrossProduct(float x, float y, float z, float a, float b, float c);
    float oldIncrement;
    float maxIncrement;

    static void drawLeg(void); // draws one leg
    static void drawLeg(GLfloat jointAngle, GLfloat jointOffset); // draw leg with an angle specified
    static void drawLegs(void);

};

#endif