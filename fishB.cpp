#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif


#include "fishB.h"
#include "math.h"
#include <iostream>

fishB::fishB() {
    x = 1;
    y = 1;
    z = 1;

    xInc = 0.1;
    yInc = 0.1;
    zInc = 0.0;
    
    angle = 40;
    Autorun = 0;
    
    colour[0]=1;
    colour[1]=1;
    colour[2]=1;
}

void fishB::draw(void) {
  // Draw Actual "Fish"
  glColor3f( colour[0], colour[1], colour[2] );

  // Draw "Fish"
  float velRatio = 1;
    // increment the fish position
    x += xInc;
    y += yInc;
    z += zInc;
  glPushMatrix();

  glTranslatef(x,y,z);                          // move to where it is right now
  getCrossProduct(xInc,yInc,zInc,0,0,-1);        // get cross product
  //    std::cout << "getangle: " << getAngle(xInc,yInc,zInc,0,0,1) << std::endl;   // debug
  glRotatef(getAngle(xInc,yInc,zInc,0,0,-1), xcp, ycp, zcp);    // rotate to look to where it is moving
  
  glEnable(GL_LIGHTING);
  
  GLfloat amDef[4], spDef[4];
  GLfloat am[] = { colour[0], colour[1], colour[2], 1 };
  GLfloat sp[] = { 0, 0.5, 1, 0.5 };
  
  glGetMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, amDef );
  glGetMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, spDef );

  glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, am );
  glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, sp );

  // Head
  glRotatef( velRatio * 0.8 * angle, 0, 1, 0 );
  glutSolidCone( 0.2, 0.4, 5, 1 );

  // Body
  glRotatef( 180 - velRatio * angle, 0, 1, 0 );
  glutSolidCone( 0.1, 0.5, 5, 1 );
  glPushMatrix();
  glTranslatef( 0, 0, 0.1 );
  glRotatef( -65, 1, 0, 0 );
  glutSolidCone( 0.08, 0.3, 5, 1 );
  glPopMatrix();
	
  // Tail
  glTranslatef( 0, 0, 0.5 );
  glRotatef( 180 + velRatio * 1.2 * angle, 0, 1, 0 );
  glTranslatef( 0, 0, -0.2 );
  glScalef( 0.5, 1, 1 );
  glutSolidCone( 0.2, 0.2, 5, 1 );
  glPopMatrix();
	
  glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, amDef );
  glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, spDef );

  glDisable(GL_LIGHTING);

  // Radius of influence
  if ( false ) {
    glColor3f( 0.2, 0.2, 0.2 );
    glutWireSphere(FOV_RADIUS, 10, 3 );
  }
  
  // Draw Axis
  if ( false ) {
    glColor3f( 1, 0, 0 );	
    glBegin( GL_LINES );
    glVertex3f(0,0,0);
    glVertex3f( 1, 0, 0 );
    glEnd();
    
    glColor3f( 0, 1, 0 );
    glBegin( GL_LINES );
    glVertex3f(0,0,0);
    glVertex3f( 0, 1, 0 );
    glEnd();
		
    glColor3f( 0, 0, 1 );
    glBegin( GL_LINES );
    glVertex3f(0,0,0);
    glVertex3f( 0, 0, 1 );
    glEnd();
  }
  
  // Draw Blind Cone
  if ( false ) {
    glPushMatrix();
    glTranslatef( 0, 0, -FOV_RADIUS );
    glutWireCone( FOV_RADIUS * tan( ( 180 - FOV_ANGLE )* PI / 180.0 ), FOV_RADIUS, 4, 1 );
    glPopMatrix();
  }		
  
  glPopMatrix();
}

void fishB::printXYZ(void) {
    std::cout << "x " << x << std::endl;
    std::cout << "y " << y << std::endl;
    std::cout << "z " << z << std::endl;
    std::cout << std::endl;
}

float fishB::vectorDistance(float x, float y, float z) {
    return (float)sqrt((x*x)+(y*y)+(z*z));
}

float fishB::getAngle(float x, float y, float z, float a, float b, float c) {
    float dot_product = (x*a) + (y*b) + (z*c);
    float div = vectorDistance(x,y,z)*vectorDistance(a,b,c);
    float arc = (float) acos(dot_product/div);
    return arc* 180.0 / PI;
}

void fishB::getCrossProduct(float x, float y, float z, float a, float b, float c) {
    xcp = (y*c)-(z*b);
    ycp = (z*a)-(x*c);
    zcp = (x*b)-(y*a);
}