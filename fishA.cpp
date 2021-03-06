#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "fishA.h"
#include "math.h"

// setup the static variables
GLfloat fishA::material[4] = {1.f, 1.f, 1.f, 1.f};
GLfloat fishA::shininess = 120.f;

// Debug only, the other one should be used
fishA::fishA() {        
        // Fish Speed
        xInc = 0.0;
        yInc = 0.1;
        zInc = -0.1;        

        // Fish Position
        x = 0;
        y = 0;
        z = -15;
                
        // Tail Animation
    	tailAngle = 40.0f;
        modeTail=0;
        angleMax = 45;
}

// position, speed and color as parameters

fishA::fishA(float posx, float posy, float posz, float velx, float vely, float velz, float A, float B, float C) {

    x = posx;
    y = posy;
    z = posz; // position
    
    xInc = velx;
    yInc = vely;
    zInc = velz; // speed
    
    cpos1 = A;
    cpos2 = B;
    cpos3 = C; // color

    // Tail Animation
    tailAngle = 40.0f;
    modeTail = 0;
    angleMax = 45;
}

void fishA::draw(void) {
    // increment the fish position
    x += xInc;
    y += yInc;
    z += zInc;
    
    glColor4f(cpos1, cpos2, cpos3,1); // semi-transparent blue bubble

    glPushMatrix();
    glTranslatef(x,y,z);
    getCrossProduct(xInc,yInc,zInc,-1,0,0);        // get cross product
 
 //   glRotatef(getAngle(xInc,yInc,zInc,1,0,0), xcp, ycp, zcp);    // rotate to look to where it is moving
 
    if((xcp!=0.0)||(ycp!=0.0)||(zcp!=0.0)) {            // orient fish to look where it's going
        glRotatef(-getAngle(xInc,yInc,zInc,-1,0,0), xcp, ycp, zcp); 
    }
    else {
        if(getAngle(xInc,yInc,zInc,-1,0,0)>179.5)
            glRotatef(180.0, 0, 1.0, 0);
    }
    
//    getCrossProduct(-1,0.2,0,1,0,0);        // get cross product
//    glRotatef(getAngle(-1,0.2,0,1,0,0), xcp, ycp, zcp);    // rotate to look to where it is moving
//    std::cout << "Angle : " << getAngle(xInc,yInc,zInc,-1,0,0) << std::endl;
//    std::cout << "vector : " << xcp << " " << ycp << " " << zcp << std::endl;
    
    // set up the material properties (only front needs to be set)
    glMaterialfv(GL_FRONT, GL_AMBIENT, material);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glEnable(GL_LIGHTING);

    GLfloat amDef[4], spDef[4];
    GLfloat am[] = {1, 1, 0, 1};
    GLfloat sp[] = {0, 0.5, 1, 0.5};

    glGetMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amDef);
    glGetMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spDef);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, am);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sp);

    // set up vertex arrays
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glNormalPointer(GL_FLOAT, 0, normal);
    glTexCoordPointer(2, GL_FLOAT, 0, texels);

    // enable vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // draw first side of the fish
    glFrontFace(GL_CCW);
    drawSide();

    // draw second side of the fish
    glScalef(1.0f, 1.0f, -1.0f);
    glFrontFace(GL_CW);
    drawSide();

    // work out new fish tail position
    /*GLfloat pt = sin(tailAngle * 3.14159 / 180);
    tailAngle += tailAngleInc;
    if (tailAngle < -tailAngleCutOff || tailAngle > tailAngleCutOff)
        tailAngleInc *= -1; */
    if(modeTail==0) {
        tailAngle = tailAngle+5;
        if(tailAngle>=angleMax)
            modeTail=1;
    }
    else {
        tailAngle = tailAngle-5;
        if (tailAngle<=-angleMax)
            modeTail=0;
    }
    
    GLfloat pt = sin(tailAngle * PI / 180);
    
    // draw one side of flexible part of the tail
    vertex[143] = vertex[152] = vertex[149] = vertex[158] = vertex[167] = pt;
    glDrawArrays(GL_TRIANGLES, 6 + (4 * 6) + (3 * 5), 3 * 4);
    glScalef(1.0f, 1.0f, -1.0f);

    // draw second side of flexible part of the tail
    glFrontFace(GL_CCW);
    vertex[143] = vertex[152] = vertex[149] = vertex[158] = vertex[167] = -pt;
    glDrawArrays(GL_TRIANGLES, 6 + (4 * 6) + (3 * 5), 3 * 4);

    // disable all vertex arrays and texturing
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    glPopMatrix();
}

void fishA::drawSide(void) {
    glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
    glDrawArrays(GL_QUADS, 6, 4 * 6);
    glDrawArrays(GL_TRIANGLES, 6 + 4 * 6, 3 * 5);
}

GLfloat fishA::vertex[] ={
    // 2				|					|					|
    0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.45f,
    // 1				|					|					|
    0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.45f, 0.5f, 0.5f, 0.0f,
    // 3				|					|					|
    0.5f, 0.0f, 0.45f, 0.5f, -0.5f, 0.0f, 1.5f, -1.0f, 0.0f, 1.5f, 0.0f, 0.45f,
    // 4				|					|					|
    0.5f, 0.5f, 0.0f, 0.5f, 0.0f, 0.45f, 1.5f, 0.0f, 0.45f, 1.5f, 1.0f, 0.0f,
    // 6				|					|					|
    1.5f, 0.0f, 0.45f, 1.5f, -1.0f, 0.0f, 2.5f, -1.0f, 0.0f, 2.5f, 0.0f, 0.45f,
    // 5				|					|					|
    1.5f, 1.0f, 0.0f, 1.5f, 0.0f, 0.45f, 2.5f, 0.0f, 0.45f, 2.5f, 1.0f, 0.0f,
    // 8				|					|					|
    2.5f, 0.0f, 0.45f, 2.5f, -1.0f, 0.0f, 3.5f, -0.5f, 0.0f, 3.5f, 0.0f, 0.2f,
    // 7				|					|					|
    2.5f, 1.0f, 0.0f, 2.5f, 0.0f, 0.45f, 3.5f, 0.0f, 0.2f, 3.5f, 0.5f, 0.0f,

    // 9
    // c				|					|					|
    3.5f, 0.5f, 0.0f, 3.5f, 0.0f, 0.2f, 3.75f, 0.4f, 0.1f,
    // b				|					|					|
    3.5f, 0.0f, 0.2f, 3.75f, -0.4f, 0.1f, 3.75f, 0.4f, 0.1f,
    // a				|					|					|
    3.5f, 0.0f, 0.2f, 3.5f, -0.5f, 0.0f, 3.75f, -0.4f, 0.1f,
    // e				|					|					|
    3.5f, 0.5f, 0.0f, 3.75f, 0.4f, 0.1f, 3.75f, 0.4f, -0.1f,
    // d				|					|					|
    3.5f, -0.5f, 0.0f, 3.75f, -0.4f, -0.1f, 3.75f, -0.4f, 0.1f,

    // 10
    // F				|					|					|
    3.75f, 0.4f, 0.1f, 3.75f, -0.4f, 0.1f, 4.3f, -0.8f, 0.0f,
    // G				|					|					|
    3.75f, 0.4f, 0.1f, 4.3f, -0.8f, 0.0f, 4.3f, 0.8f, 0.0f,
    // I				|					|					|
    3.75f, 0.4f, 0.1f, 4.3f, 0.8f, 0.0f, 3.75f, 0.4f, -0.1f,
    // H				|					|					|
    3.75f, -0.4f, -0.1f, 4.3f, -0.8f, 0.0f, 3.75f, -0.4f, 0.1f
};

GLfloat fishA::normal[] ={
    // 2				|					|					|
    -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    // 1				|					|					|
    -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    // 4				|					|					|
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    // 3				|					|					|
    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    // 6				|					|					|
    0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    // 5				|					|					|
    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    // 8				|					|					|
    0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    // 7				|					|					|
    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // 9
    // c				|					|					|
    0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.71f, 0.71f,
    // b				|					|					|
    0.0f, -0.71f, 0.71f, 0.0f, 0.0f, 1.0f, 0.0f, -0.71f, 0.71f,
    // a				|					|					|
    0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -0.71f, 0.71f,
    // e				|					|					|
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    // d				|					|					|
    0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

    // 10
    // F				|					|					|
    0.0f, -0.71f, 0.71f, 0.71f, -0.71f, 0.0f, 0.71f, -0.71f, 0.0f,
    // G				|					|					|
    0.0f, -0.71f, 0.71f, 0.71f, -0.71f, 0.0f, 0.71f, 0.71f, 0.0f,

    // I				|					|					|
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    // H				|					|					|
    0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f
}; 

GLfloat fishA::texels[] ={
    // 2					|						|						|
    126.f / 128.f, 68.f / 128.0f, 119.f / 128.f, 47.f / 128.f, 112.f / 128.f, 68.f / 128.f,
    // 1					|						|						|
    126.f / 128.f, 68.f / 128.0f, 112.f / 128.f, 68.f / 128.f, 117.f / 128.f, 84.f / 128.f,
    // 4					|						|						|
    112.f / 128.f, 68.f / 128.f, 119.f / 128.f, 47.f / 128.f, 86.f / 128.f, 8.f / 128.f, 84.f / 128.f, 68.f / 128.f,
    // 3					|						|						|
    117.f / 128.f, 84.f / 128.f, 112.f / 128.f, 68.f / 128.f, 84.f / 128.f, 68.f / 128.f, 83.f / 128.f, 120.f / 128.f,
    // 6					|						|						|
    84.f / 128.f, 68.f / 128.f, 86.f / 128.f, 8.f / 128.f, 52.f / 128.f, 15.f / 128.f, 53.f / 128.f, 68.f / 128.f,
    // 5					|						|						|
    83.f / 128.f, 120.f / 128.f, 84.f / 128.f, 68.f / 128.f, 53.f / 128.f, 68.f / 128.f, 54.f / 128.f, 110.f / 128.f,
    // 8					|						|						|
    53.f / 128.f, 68.f / 128.f, 52.f / 128.f, 15.f / 128.f, 26.f / 128.f, 54.f / 128.f, 25.f / 128.f, 69.f / 128.f,
    // 7					|						|						|
    54.f / 128.f, 110.f / 128.f, 53.f / 128.f, 68.f / 128.f, 25.f / 128.f, 69.f / 128.f, 28.f / 128.f, 76.f / 128.f,

    // 9
    // c					|						|						|
    28.f / 128.f, 74.f / 128.f, 25.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,
    // b					|						|						|
    25.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,
    // a					|						|						|
    25.f / 128.f, 69.f / 128.f, 26.f / 128.f, 54.f / 128.f, 20.f / 128.f, 69.f / 128.f,
    // e					|						|						|
    26.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,
    // d					|						|						|
    26.f / 128.f, 54.f / 128.f, 20.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,

    // 10
    // F					|						|						|
    20.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f,
    // G					|						|						|
    20.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f,
    // I					|						|						|
    20.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f,
    // H					|						|						|
    20.f / 128.f, 69.f / 128.f, 5.f / 128.f, 69.f / 128.f, 20.f / 128.f, 69.f / 128.f
};