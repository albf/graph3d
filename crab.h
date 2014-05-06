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

    static GLfloat material[4];
    static GLfloat shininess;
    GLUquadricObj *quadric; // quadric object for all renderables

private:
    float oldIncrement;
    float maxIncrement;

    static void drawLeg(void); // draws one leg
    static void drawLeg(GLfloat jointAngle, GLfloat jointOffset); // draw leg with an angle specified
    static void drawLegs(void);

};

#endif