/* 
 * File:   seaFloor.h
 * Author: root
 *
 * Created on May 5, 2014, 11:59 AM
 */

#ifndef SEAFLOOR_H
#define	SEAFLOOR_H

#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "renderable.h"
#include <iostream>
#include <stdio.h>
#include <iostream>


class seaFloor : public Renderable {
public:
    seaFloor();
    virtual void draw();
    void printXYZ(void);
    virtual void init(Viewer &);
    
    void setPos(float nx, float ny, float nz) {
        x=nx; y=ny; z=nz;
    }
    
    
    float x, y, z; // Position

private:
    GLubyte* readPPMfile(char* filename);
    float i;
};

#endif	/* SEAFLOOR_H */