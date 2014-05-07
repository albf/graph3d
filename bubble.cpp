#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "bubble.h"

using namespace std;

// Constructor for debug, the other one should be used.
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

// (posx, posy, posz) -> initial position
// size average : average size of a bubble
// error : how much it can be larger.
Bubble::Bubble(float posx, float posy, float posz, float size_average, float error) {
    x = posx;       // initial position.
    y = posy;
    z = posz;

    xInc = 0.0;     // speed
    yInc = 0.015;
    zInc = 0.0;

    size = size_average+((float)((float)rand()/(float)RAND_MAX)*error);  // size of the bubble
    time=0;

    // Animation A  :: "Blinking" Effect of the bubbles. It gets a little larger
    // and them it comes back to the original state.
    size_variation=size_average/5;      // Variation of the original size size.   
    cycle_growth = 1/size_variation;    // Variable for calculation
    cycle_animate1=15;                  // Cycles that this will happen
    momentA=0;                          // For the state machine.
    
    // Animation B  :: "Growth" Effect of the bubbles. It will get larger as it
    // will come up. It uses a log() function.
    increase_factor=size_average/4;     // factor of growth
    increase_speed=1;                   // speed of increase
    
    // Animation C  :: "Dancing" Effect of the bubbles. It will make a little dance
    // in the (x,z) plane (as the Y axis is up/down).
    anim3Z = (float)((float)rand()/(float)RAND_MAX);    // Part in Z direction, random.
    anim3X = sqrt(1-(anim3Z*anim3Z));                   // Part in X direction, complement Z part.
    cycle_animate3=30;                                  // Cycles involved.
    anim3Scale = size_average/5;                        // Scale of the dance.
}

void Bubble::animate(void) {
    time++; // update type

    if ((time % cycle_animate1) == 0) { 
        if (momentA == 0)
            momentA = 1;
        else
            momentA = 0;
    }
    
    // Growth used in animation A are calculated
    if (momentA == 0)
        cycle_growth = ((float)((int)time % (int)cycle_animate1)) / (float) cycle_animate1;
    else
        cycle_growth = (cycle_animate1 - (float) ((int) time % (int) cycle_animate1)) / (float) cycle_animate1;


    // Cos used in the Animation 3 are calculated
    float angle = (((float)((int)time%(int)cycle_animate3))/((float)cycle_animate3))*360;
    deltaX = anim3Scale * anim3X * (float)cos(deg2rad(angle));
    deltaZ = anim3Scale * anim3Z * (float)cos(deg2rad(angle));
}

void Bubble::draw(void) {

    x += xInc;
    y += yInc;
    z += zInc;
    
    glColor4f(0.74902, 0.847059, 0.847059, 0.3); // semi-transparent blue bubble
    glPushMatrix();
    glTranslatef(x+deltaX, y, z+deltaZ);         // move and apply Animation 3
    //glTranslatef(x, y, z);
    
    // Scale and apply animation 1 and 2.
    glScalef(   (1.0f+((double)(cycle_growth))*(double)size_variation)+(log((double)(increase_speed*(double)time))*(double)increase_factor),
                (1.0f+((double)(cycle_growth))*(double)size_variation)+(log((double)(increase_speed*(double)time))*(double)increase_factor),
                (1.0f+((double)(cycle_growth))*(double)size_variation)+(log((double)(increase_speed*(double)time))*(double)increase_factor));
    
    
    glutSolidSphere(size, 20, 20);  // Create Sphere
    glPopMatrix();
}