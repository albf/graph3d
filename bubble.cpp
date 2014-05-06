#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "bubble.h"

using namespace std;

Bubble::Bubble() {
    x = 1;
    y = -3;
    z = +25;
    
    xInc = 0.00;
    yInc = 0.015;
    zInc = 0.00;
    
    size=0.5;
    time=0;
    
    // Animation A
    size_variation=0.1;
    cycle_growth = 1/size_variation;
    cycle_animate1=10;
    momentA=0;
    
    // Animation B
    increase_factor=0.125;
    increase_speed=1;
    
    // Animation C
    anim3X = (rand()/RAND_MAX);
    anim3Z = sqrt(1-(anim3X*anim3X));
    cycle_animate3=20;
    anim3Scale = 1;
}

Bubble::Bubble(float posx, float posy, float posz, float size_average, float error) {
    x = posx;
    y = posy;
    z = posz;

    xInc = 0.0;
    yInc = 0.015;
    zInc = 0.0;

    size = size_average+((float)((float)rand()/(float)RAND_MAX)*error);  // size of the bubble
    time=0;

    // Animation A
    size_variation=size_average/5;
    cycle_growth = 1/size_variation;
    cycle_animate1=15;
    momentA=0;
    
    // Animation B
    increase_factor=size_average/4;
    increase_speed=1;
    
    // Animation C
    anim3Z = (float)((float)rand()/(float)RAND_MAX);
    anim3X = sqrt(1-(anim3Z*anim3Z));
    cycle_animate3=30;
    anim3Scale = size_average/5;
}

void Bubble::animate(void) {
    time++;

    if ((time % cycle_animate1) == 0) {
        if (momentA == 0)
            momentA = 1;
        else
            momentA = 0;
    }

    if (momentA == 0)
        cycle_growth = (time % cycle_animate1) / (float) cycle_animate1;
    else
        cycle_growth = (cycle_animate1 - (float) ((int) time % (int) cycle_animate1)) / (float) cycle_animate1;


    float angle = (((float)((int)time%(int)cycle_animate3))/((float)cycle_animate3))*360;
    deltaX = anim3Scale * anim3X * (float)cos(deg2rad(angle));
    deltaZ = anim3Scale * anim3Z * (float)cos(deg2rad(angle));

    //cout << "deltax : " << deltaX << endl;
}

void Bubble::draw(void) {

    x += xInc;
    y += yInc;
    z += zInc;
    
    glColor4f(0.74902, 0.847059, 0.847059, 0.3); // transparent bubble
    glPushMatrix();
    glTranslatef(x+deltaX, y, z+deltaZ);
    //glTranslatef(x, y, z);
    
    glScalef(   (1.0f+((double)(cycle_growth))*(double)size_variation)+(log((double)(increase_speed*(double)time))*(double)increase_factor),
                (1.0f+((double)(cycle_growth))*(double)size_variation)+(log((double)(increase_speed*(double)time))*(double)increase_factor),
                (1.0f+((double)(cycle_growth))*(double)size_variation)+(log((double)(increase_speed*(double)time))*(double)increase_factor));
    
    //double value = log((double)(increase_speed*(float)time));
    //cout << "Log : " << (double)log((double)(increase_speed*(double)time)) << endl;
    
    glutSolidSphere(size, 20, 20);
    glPopMatrix();
}