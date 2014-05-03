#ifndef _fishA_
#define _fishA_

#include "renderable.h"
#include <iostream>
#include <stdio.h>
#define FISH_TEXTURE 2

class fishA : public Renderable {
public:
    fishA();
    virtual void draw();
    void printXYZ(void);

    GLfloat x, y, z; // position of object
    GLfloat rx,ry, rz; // rotation angle of object
    GLfloat sx,sy,sz; // scale of object
    GLfloat xInc, yInc, zInc;   // speed of object

    static unsigned int textures[2]; /// texture id array
    static GLUquadricObj *quadric; /// quadric object for all renderables

private:             	
    GLfloat tailAngle;
    GLfloat tailAngleCutOff;
    GLfloat tailAngleInc;
    static GLfloat vertex[]; /// vertex array data
    static GLfloat normal[]; /// normals for each vertex
    static GLfloat texels[]; /// texture coords for each vertex
    static GLfloat colours[]; /// colour array data
    static GLfloat material[4];
    static GLfloat shininess;

    void drawSide();

};

#endif