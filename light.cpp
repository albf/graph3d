#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "light.h"

Light::Light(void)
{
	lightPosition[0] = 0.0f; //x 
	lightPosition[1] = 30.0f; //y 
	lightPosition[2] = 0.0f; //z 
	lightPosition[3] = 1.0f; //w
	
	diffuseProperty[0] = 1.0f ; //y
	diffuseProperty[1] = 1.0f ; //y
	diffuseProperty[2] = 1.0f ; //z

	materialDiffuseProp[0] = 1.0f;//x
	materialDiffuseProp[1] = 1.0f;//y
	materialDiffuseProp[2] = 1.0f;//z
	materialDiffuseProp[3] = 1.0f;//q

	dList = glGenLists(1);
	glNewList(dList,GL_COMPILE);

		glColor4f(diffuseProperty[0],diffuseProperty[1],diffuseProperty[2],1);
		glutSolidSphere(1,40,40);

	// endList
	glEndList();

}

Light::~Light(void)
{
	

}


void Light::apply(void)
{

	//glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuseProperty); 
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseProp );
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void Light::draw() {
/*    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  // set light as diffuse
    glLightfv(GL_LIGHT0, GL_DIFFUSE, specular);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    GLfloat lightpos[] = {0, 5., 0., 1.};          // set position of the light
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    
    glEnable(GL_LIGHT0);
*/    
    glPushMatrix(); 
    
//    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(0,3,0);
    glCallList(dList);
    
    glPopMatrix();


}
