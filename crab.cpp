#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "crab.h"
#define PI 3.14159

// static variables
GLfloat crab::material[4] = {0.5f, 0.5f, 0.5f, 1.f};
GLfloat crab::shininess = 50.f;

// default constructor
crab::crab() {
    x = 1;    y = -5;    z = +25;
    xInc = 0.01;    yInc = 0.0;    zInc = +0.05;
    
    quadric = gluNewQuadric();
    oldIncrement=sqrt((xInc*xInc)+(zInc*zInc))*0.1;
}

// constructor with parameters
crab::crab(float posx, float posz,float velx, float velz) {
    x = posx; y = -5; z=posz;
    xInc = velx; yInc = 0.0; zInc = velz;
    quadric = gluNewQuadric();
    oldIncrement=sqrt((xInc*xInc)+(zInc*zInc))*0.1;
}

// method used to update the position of the crab
// It tries to put some smooth random in the movements of the crabs.
void crab::animate(void) {
    float speed = sqrt((xInc*xInc)+(zInc*zInc));
    maxIncrement = speed*0.1;
    float Increment = (2*maxIncrement*((float)rand()/(float)RAND_MAX))-maxIncrement;
    float zdelta;
    
    Increment = (oldIncrement*9+Increment)/10;
    
    xInc=xInc+Increment;
    //speed = sqrt((xInc*xInc)+(zInc*zInc));
    if ((speed * speed)>(xInc * xInc)) {
        zdelta = sqrt((speed * speed)-(xInc * xInc));
        if (zInc >= 0)
            zInc = +zdelta;
        else
            zInc = -zdelta;
    }
    
    else {
        zInc=0;
        xInc=speed;
    }
    
    
    oldIncrement=Increment; 
}

// method used to modelize the crab
void crab::draw(void) {
    // increment the crab position
    x += xInc;
    y += yInc;
    z += zInc;
    glPushMatrix();
    glTranslatef(x, y, z); // move to where it is right now
    glRotatef(180, 0, 0, 1);

    //  getCrossProduct(xInc, yInc, zInc, 0, 0, 1); // get cross product    // debug
    //  glRotatef(getAngle(xInc, yInc, zInc, 0, 0, 1), xcp, ycp, zcp); // rotate to look to where it is moving
    //glRotatef(180, xInc, yInc, zInc-(vectorDistance(xInc,yInc, zInc)));
    //glRotatef(180,)
    //   std::cout << "Angle : " << getAngle(xInc,yInc,zInc,0,0,1) << std::endl;
    //   std::cout << "vector : " << x << " " << y << " " << z << std::endl;

    if ((xcp != 0.0) || (ycp != 0.0) || (zcp != 0.0)) { // orient fish to look where it's going
        glRotatef(-getAngle(xInc,yInc,zInc,0,0,1), 0, 1.0, 0); 
    }
    else {
        if(getAngle(xInc,yInc,zInc,0,0,1)>179.5)
            glRotatef(180.0, 0, 1.0, 0);
    }
    
    
    glColor3f(1.0f, 0.45f, 0.45f);

    // body
    glPushMatrix();
    glScalef(1.0f, 0.5f, 1.0f);
    gluSphere(quadric, 0.3f, 16, 16);
    glPopMatrix();

    // legs
    glPushMatrix();
    drawLegs();
    glScalef(-1.f, 1.f, 1.f);
    glFrontFace(GL_CW);
    drawLegs();
    glFrontFace(GL_CCW);
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);

    // left eye
    glTranslatef(-0.06f, 0.0f, 0.3f);
    glutSolidSphere(0.05f, 12, 8);

    // right eye
    glTranslatef(0.12f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 12, 8);

    glPopMatrix();
}

// Draws a leg using an angle
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

	// draw fourth leg
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.00f);
	glRotatef(-65.0f, -0.2f, 1.0f, 0.0f);
	drawLeg(0.0f, 0.0f);
	glPopMatrix();

	// alteration of the color
	glColor3f(1.0f, 0.65f, 0.65f);

	// front leg
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(55.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg();
	glPopMatrix();

	// arms
	glPushMatrix();
	glTranslatef(0.24f, 0.0f, 0.725f);
	glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg(-60.0f, 0.1f);
	glPopMatrix();
}