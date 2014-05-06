#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "diver.h"

void setcolor(float c[], int r, int g, int b) {
    c[0] = r;
    c[1] = g;
    c[2] = b;
}

Diver::Diver(double taille) {
    ratio = taille;
    corps = taille;
    tete = taille / 10.;
    main = taille / 22.;
    pied = taille / 6;
    cou = taille / 11.;
    avant_bras = taille / 6;
    bras = taille / 6;
    cuisse = taille / 5.;
    tibiat = taille / 5.;
    tronc = corps - cuisse - tibiat - taille / 4;

    angle_bras_mv = 0;

    int blackorwhite = rand() % 2;
    if (blackorwhite == 0) {
        setcolor(skinc, 0, 1, 1);
    } else {
        setcolor(skinc, 1, 0.0, 0.0);
    }
    setcolor(bodyc, 1, 1, 0.2);
    setcolor(footc, 0, 0.9, 1);
    setcolor(legc, 1, 1, 1);

    time = 0;
    animation = 1;
    x = 0;
    y = -1.2;
    z = 20  ;
    xInc = 0.00;
    yInc = 0.00;
    zInc = -0.02;
    stageLeg=0;
    speedLeg=1.0;
    speedLeg2=1.3;
    stageLimit=12;
}

void Diver::animate(void) {

    if(stageLeg==0) {
        if(time>stageLimit) {
            time-=1;
            stageLeg=1;
        }
        else
            time++;
    }
    else {
        if(time<((-1)*stageLimit)) {
            time++;
            stageLeg=0;
        }
        else
            time--;
    }

}

void Diver::draw() {
    // increment the crab position
    x += xInc;
    y += yInc;
    z += zInc;
    //time++;

    glPushMatrix();

    glTranslatef(x, y, z); // move to where it is right now
    getCrossProduct(xInc, yInc, zInc, 0, 0, -1); // get cross product
    //    std::cout << "getangle: " << getAngle(xInc,yInc,zInc,0,0,1) << std::endl;   // debug
    glRotatef(getAngle(xInc, yInc, zInc, 0, 0, -1), xcp, ycp, zcp); // rotate to look to where it is moving

    glRotated(-90, 1, 0, 0); // Le bonhomme est allongé
    glRotated(180, 0, 0, 1);    // fix position
    glTranslatef(0, 0, cuisse + tibiat + main); // On fait le haut du corps

    glColor3fv(bodyc);
    gluCylinder(gluNewQuadric(), tronc / 5, tronc / 5, tronc, 10, 10);

    glPushMatrix();
    glTranslatef(0, 0, tronc); // On fait le haut du corps
    glColor3fv(skinc);

    gluCylinder(gluNewQuadric(), tronc / 5, tronc / 10, cou, 10, 10);

    glPushMatrix(); // La tete
    
    glTranslatef(0, 0, cou + tete / 2);
    gluSphere(gluNewQuadric(), tete, 10, 10);

    
    mask = ratio/30.0f; // mask 
    // std::cout << "mask " << mask << std::endl;   // debug
    glTranslatef(-tete,-1.2*tete,0);
    glRotatef(90,0,1,0);
    cylinder(50,0,mask,mask*5);    // solid cylinder
    glTranslatef(-tete*1.8,0,tete/8);
    glRotatef(90,0,1,0);
    cylinder(50,0,0.8*mask,ratio/5);    // solid cylinder
    
    glPopMatrix(); // Fin haut du corps

    double ecart_bras_epaule = 120; // ecartement bras épaule
    double ecart_bras_avant_bras = 60; // ecartement bras épaule
    angle_bras_mv = time;
    
    glPushMatrix(); 


    glPushMatrix(); // un bras 1
    glRotated(angle_bras_mv, 1, 0, 0);
    glRotated(ecart_bras_epaule, 0, 1, 0);
    glColor3fv(bodyc);
    gluCylinder(gluNewQuadric(), bras / 8, bras / 10, bras, 10, 10);
    glTranslatef(0, 0, bras);

    glRotated(ecart_bras_avant_bras, 0, 1, 0);
    gluCylinder(gluNewQuadric(), bras / 10, avant_bras / 10, avant_bras, 10, 10);
    glTranslatef(0, 0, bras);
    glColor3fv(skinc);
    gluSphere(gluNewQuadric(), main, 10, 10); // Une main

    glPopMatrix(); // Fin bras 1


    glPushMatrix(); // un bras 2
    glRotated(-angle_bras_mv, 1, 0, 0);
    glRotated(-ecart_bras_epaule, 0, 1, 0);
    glColor3fv(bodyc);
    gluCylinder(gluNewQuadric(), bras / 8, bras / 10, bras, 10, 10);
    glTranslatef(0, 0, bras);

    glRotated(ecart_bras_avant_bras, 0, -1, 0);
    gluCylinder(gluNewQuadric(), bras / 10, avant_bras / 10, avant_bras, 10, 10);
    glTranslatef(0, 0, bras);
    glColor3fv(skinc);
    gluSphere(gluNewQuadric(), main, 10, 10); // Une main

    glPopMatrix(); // Fin bras 2

    glPopMatrix(); // Fin mouvement bras;

    glPopMatrix(); // retour au bas du corps...
    
    double ecart_jambe = (double)time*speedLeg; // demi écartement des jambes
    double ecart_jambe2a = time*speedLeg2;
    double ecart_jambe2b = time*speedLeg2;
    
    if(time>0)
        ecart_jambe2a=0;
    else
        ecart_jambe2b=0;
    
    glPushMatrix(); // debut jambe 1
    
    glColor3fv(legc);
    glRotated(180-15, 0, 1, 0);
    glRotated((ecart_jambe*speedLeg)-15, 1, 0, 0);
    gluCylinder(gluNewQuadric(), cuisse / 3, cuisse / 4, cuisse, 10, 10);
    
    glTranslatef(0, 0, cuisse);
    glRotated((ecart_jambe2a), 1, 0, 0);
    gluCylinder(gluNewQuadric(), cuisse / 4, tibiat / 4, tibiat, 10, 10);
    
    glTranslatef(0, 0, tibiat);
    glRotated(45, 1, 0, 0);
    glColor3fv(footc);
    gluCylinder(gluNewQuadric(), pied / 4, pied / 6, pied, 10, 10);


    glPopMatrix(); // fin jambe 1


    glPushMatrix(); // debut jambe 2
    
    glColor3fv(legc);
    glRotated(180+15, 0, 1, 0);
    glRotated((ecart_jambe*speedLeg)+15, -1, 0, 0);
    gluCylinder(gluNewQuadric(), cuisse / 3, cuisse / 4, cuisse, 10, 10);

    glTranslatef(0, 0, cuisse);
    glRotated((ecart_jambe2b), -1, 0, 0);
    gluCylinder(gluNewQuadric(), cuisse / 4, tibiat / 4, tibiat, 10, 10);
    glTranslatef(0, 0, tibiat);

    glRotated(45, 1, 0, 0);
    glColor3fv(footc);
    gluCylinder(gluNewQuadric(), pied / 4, pied / 6, pied, 10, 10);

    glPopMatrix(); // fin jambe 2
    glPopMatrix(); // Retour à rien du tout...
}

void Diver::cylinder(int n, int arg, float mult, float v)
{
    // DumbProof Double Check :)
    if (arg < 0)
        arg = 0;
 
    // Cylinder Bottom
    glBegin(GL_POLYGON);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        for(int i = arg; i <= (360 + arg); i += (360 / n)) {
            float a = i * M_PI / 180; // degrees to radians
            glVertex3f(mult * cos(a), mult * sin(a), 0.0);
        }
    glEnd();
 
    // Cylinder Top
    glBegin(GL_POLYGON);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        for(int i = arg; i <= (360 + arg); i += (360 / n)) {
            float a = i * M_PI / 180; // degrees to radians
            glVertex3f(mult * cos(a), mult * sin(a), v);
        }
    glEnd();
 
    // Cylinder "Cover"
    glBegin(GL_QUAD_STRIP);
        glColor4f(1.0, 1.0, 0.0, 1.0);
        for(int i = arg; i < 480; i += (360 / n)) {
            float a = i * M_PI / 180; // degrees to radians
            glVertex3f(mult * cos(a), mult * sin(a), 0.0);
            glVertex3f(mult * cos(a), mult * sin(a), v);
        }
    glEnd();
 

}