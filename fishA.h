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

    GLfloat x; /// x position of object
    GLfloat y; /// y position of object
    GLfloat z; /// z position of object

    GLfloat rx; /// x rotation angle of object
    GLfloat ry; /// y rotation angle of object
    GLfloat rz; /// z rotation angle of object

    GLfloat sx; /// x scale of object
    GLfloat sy; /// y scale of object
    GLfloat sz; /// z scale of object

    bool isList; /// is this a display list object?

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