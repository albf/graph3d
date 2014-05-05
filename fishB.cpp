#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#define FOV_RADIUS 3           // Radius of field of view
#define FOV_ANGLE 110          // Radius of field of view angle

#include "fishB.h"
#include "math.h"

fishB::fishB() {
    x = 1;
    y = 1;
    z = 1;

    xInc = 0;
    yInc = -0.1;
    zInc = 0;
    
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

  glTranslatef(x,y,z);
  glRotatef(90, 1,0,0);     // correction
  
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
  if ( true ) {
    glColor3f( 0.2, 0.2, 0.2 );
    glutWireSphere(FOV_RADIUS, 10, 3 );
  }
  
  // Draw Axis
  if ( true ) {
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
  if ( true ) {
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
