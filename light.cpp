#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "light.h"

Light::Light(void)
{
        time=0;
}

Light::~Light(void)
{
	

}

// Draw simple lights in the scene
void Light::draw() {    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    time=time+1;

    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  // set light as diffuse
    glLightfv(GL_LIGHT0, GL_DIFFUSE, specular);
    
    float lightpos[] = {0, 50, 0., 1.};          // set position of the light
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    
    glEnable(GL_LIGHT0);
}
