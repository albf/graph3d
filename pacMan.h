#ifndef PACMAN_H_
#define PACMAN_H_

#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "renderable.h"
#include <iostream>

class pacMan : public Renderable {
private:
    // Position and moviment
    int animation;
    int time;
    int modeTime;
    float scale;

public:
    pacMan(float posx, float posy, float posz, float velx, float vely, float velz, float Nscale);
    void draw();
    void animate();
};

#endif
