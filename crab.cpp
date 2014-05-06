#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "crab.h"
#define PI 3.14159

// setup the static variables
GLfloat crab::material[4] = {0.5f, 0.5f, 0.5f, 1.f};
GLfloat crab::shininess = 50.f;

crab::crab() {
    x = 1;    y = -3;    z = +25;
    xInc = 0.01;    yInc = 0.0;    zInc = +0.05;
    
    quadric = gluNewQuadric();
    oldIncrement=sqrt((xInc*xInc)+(zInc*zInc))*0.1;
}

crab::crab(float posx, float posz,float velx, float velz) {
    x = posx; y = -3; z=posz;
    xInc = velx; yInc = 0.0; zInc = velz;
    quadric = gluNewQuadric();
    oldIncrement=sqrt((xInc*xInc)+(zInc*zInc))*0.1;
}

void crab::animate(void) {
    float speed = sqrt((xInc*xInc)+(zInc*zInc));
    float Increment = (2*maxIncrement*rand()/RAND_MAX)-maxIncrement;
    float zdelta;
    
    Increment = (oldIncrement*9+Increment)/10;

    xInc=xInc+Increment;
    zdelta = sqrt((speed*speed)-(xInc*xInc));
    if(zInc>=0) 
        zInc=zdelta;
    else
        zInc=-zdelta; 
    
    oldIncrement=Increment;
}

void crab::draw(void) {
    // increment the fish position
    x += xInc;
    y += yInc;
    z += zInc;
    glPushMatrix();
    glTranslatef(x, y, z); // move to where it is right now
    glRotatef(180, 0, 0, 1);
    
    getCrossProduct(xInc, yInc, zInc, 0, 0, 1); // get cross product
    //    std::cout << "getangle: " << getAngle(xInc,yInc,zInc,0,0,1) << std::endl;   // debug
    glRotatef(getAngle(xInc, yInc, zInc, 0, 0, 1), xcp, ycp, zcp); // rotate to look to where it is moving
    


    // get our pinky colour
    glColor3f(1.0f, 0.45f, 0.45f);

    // draw crab body (squashed along Y axis
    glPushMatrix();
    glScalef(1.0f, 0.5f, 1.0f);
    gluSphere(quadric, 0.3f, 16, 16);
    glPopMatrix();

    // draw all of the legs
    glPushMatrix();
    drawLegs();
    glScalef(-1.f, 1.f, 1.f);
    glFrontFace(GL_CW);
    drawLegs();
    glFrontFace(GL_CCW);
    glPopMatrix();

    // set to use our black colour
    glColor3f(0.0f, 0.0f, 0.0f);

    // draw left crab eye
    glTranslatef(-0.06f, 0.0f, 0.3f);
    glutSolidSphere(0.05f, 12, 8);

    // draw right crab eye
    glTranslatef(0.12f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 12, 8);

    glPopMatrix();
}

// Draws a leg using an angle between the two bones
void crab::drawLeg(GLfloat jointAngle, GLfloat jointOffset)
{
	// draw first part of a leg
	glPushMatrix();
	glTranslatef(-0.38f, 0.0f, 0.0f);
	glScalef(3.0f, 1.0f, 1.0f);
	glutSolidCube(0.06f);
	glPopMatrix();

	// draw second part of a leg
	glPushMatrix();
	glTranslatef(-0.53f, jointOffset, 0.0f);
	glRotatef(jointAngle, 0.0f, 0.0f, 1.0f);
	glScalef(4.0f, 1.0f, 1.0f);
	glutSolidCube(0.06f);
	glPopMatrix();
}

// Draws one leg
void crab::drawLeg()
{
	drawLeg(-45.0f, 0.075f);
}

// Draws complete set of legs (side legs)
void crab::drawLegs()
{
	// set a darker pinky colour for legs
	glColor3f(1.0f, 0.55f, 0.55f);

	// draw three side legs
	for (GLfloat i = -15.0f; i <= 15.0f; i += 15.0f)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -0.025f);
		glRotatef(i, 0.0f, 1.0f, 0.0f);
		drawLeg();
		glPopMatrix();
	}

	// draw fourth leg (the straight and bent downwards leg)
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.00f);
	glRotatef(-65.0f, -0.2f, 1.0f, 0.0f);
	drawLeg(0.0f, 0.0f);
	glPopMatrix();

	// set a light pinky colour for front legs
	glColor3f(1.0f, 0.65f, 0.65f);

	// front leg (arm)
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(55.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg();
	glPopMatrix();

	// front clippers on the front leg (arm)
	glPushMatrix();
	glTranslatef(0.24f, 0.0f, 0.725f);
	glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg(-60.0f, 0.1f);
	glPopMatrix();
}