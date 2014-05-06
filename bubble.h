#ifndef _bubble_
#define _bubble_

#include "renderable.h"
#include <iostream>

class Bubble : public Renderable {
public:
    Bubble();
    Bubble(float posx, float posy, float posz, float size_average, float error);
    virtual void draw();
    virtual void animate();
    
private:
    int time;
    float size;
    
    // Animation 1
    float size_variation;
    float cycle_growth;
    int cycle_animate1;
    int momentA;
    
    // Animation 2
    float increase_factor;
    float increase_speed;
    
    // Animation 3
    float anim3X;
    float anim3Z;
    float anim3Scale;
    int cycle_animate3;
    float deltaX;
    float deltaZ;
};

#endif