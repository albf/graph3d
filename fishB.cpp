#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "fishB.h"

fishB::fishB() {
    x = 1;    y = 1;    z = 1;

    xSpeed = 0.1;    ySpeed = 0.0;    zSpeed = 0.0;
    
    angle = 40;   Autorun = 0;   
    colour[0]=1;    colour[1]=1;    colour[2]=1;   
    animation=1;    time=0;
    animate();  // get the first values for incrementals;
}

fishB::fishB(float posx, float posy, float posz,float velx, float vely, float velz,float colorA, float colorB, float colorC) {
    x = posx; y=posy; z=posz;
    xSpeed = velx; ySpeed = vely; zSpeed = velz;
    colour[0]=colorA;    colour[1]=colorB;    colour[2]=colorC;   
    
    angle = 40;   Autorun = 0;   
    animation=1;    time=0;
    animate();  // get the first values for incrementals;        
}

void fishB::animate(void) {
    time = time + 5; // updates time for animation
    if (time > 70)
        time = 0;

    if (animation = 1) {
        xInc = xSpeed * cos(deg2rad((float) time));
        yInc = ySpeed * cos(deg2rad((float) time));
        zInc = zSpeed * cos(deg2rad((float) time));
    }
}

void fishB::draw(void) {
    // Draw fishB
    
    //printXYZInc();        // Debug
    
    glColor3f(colour[0], colour[1], colour[2]);

    // Draw "Fish"
    float velRatio = 1;
    // increment the fish position
    x += xInc;
    y += yInc;
    z += zInc;
    glPushMatrix();

    glTranslatef(x, y, z); // move to where it is right now
    getCrossProduct(xSpeed, ySpeed, zSpeed, 0, 0, -1); // get cross product
    //std::cout << "getangle: " << getAngle(xInc,yInc,zInc,0,0,1) << std::endl;   // debug
    glRotatef(getAngle(xSpeed, ySpeed, zSpeed, 0, 0, -1), xcp, ycp, zcp); // rotate to look to where it is moving

    glEnable(GL_LIGHTING);

    GLfloat amDef[4], spDef[4];
    GLfloat am[] = {colour[0], colour[1], colour[2], 1};
    GLfloat sp[] = {0, 0.5, 1, 0.5};

    glGetMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amDef);
    glGetMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spDef);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, am);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sp);

    // Head
    glRotatef(velRatio * 0.8 * angle, 0, 1, 0);
    glutSolidCone(0.2, 0.4, 5, 1);

    // Body
    glRotatef(180 - velRatio * angle, 0, 1, 0);
    glutSolidCone(0.1, 0.5, 5, 1);
    glPushMatrix();
    glTranslatef(0, 0, 0.1);
    glRotatef(-65, 1, 0, 0);
    glutSolidCone(0.08, 0.3, 5, 1);
    glPopMatrix();

    // Tail
    glTranslatef(0, 0, 0.5);
    glRotatef(180 + velRatio * 1.2 * angle, 0, 1, 0);
    glTranslatef(0, 0, -0.2);
    glScalef(0.5, 1, 1);
    glutSolidCone(0.2, 0.2, 5, 1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amDef);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spDef);

    glDisable(GL_LIGHTING);

    // Radius of influence
    if (false) {
        glColor3f(0.2, 0.2, 0.2);
        glutWireSphere(FOV_RADIUS, 10, 3);
    }

    // Draw Axis
    if (false) {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glEnd();

        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);
        glEnd();

        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);
        glEnd();
    }

    // Draw Blind Cone
    if (false) {
        glPushMatrix();
        glTranslatef(0, 0, -FOV_RADIUS);
        glutWireCone(FOV_RADIUS * tan((180 - FOV_ANGLE) * PI / 180.0), FOV_RADIUS, 4, 1);
        glPopMatrix();
    }

    glPopMatrix();
}