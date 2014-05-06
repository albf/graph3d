#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "diver.h"

void setcolor(float c[],int r, int g, int b) {
  c[0] = r/(double)255;
  c[1] = g/(double)255;
  c[2] = b/(double)255;
}

Diver::Diver(double taille){

	ratio = taille;
	
	corps = taille;
	tete = taille/10.;
	main = taille/22.;
	pied = taille/6;
	cou = taille/11.;
	avant_bras = taille/6;
	bras = taille/6;
	cuisse = taille/5.;
	tibiat = taille/5.;
	tronc = corps-cuisse-tibiat-taille/4;

	angle_bras_mv = 0;

	int blackorwhite = rand()%4;
	if (blackorwhite == 0) {
	  setcolor(skinc,50,20,20);
	} else {
	  setcolor(skinc,248,195,223);
	}
	setcolor(bodyc,rand()%255,rand()%255,rand()%255);
	setcolor(footc,rand()%255,rand()%255,rand()%255);
	setcolor(legc,rand()%255,rand()%255,rand()%255);
        
        time=0;
        animation=1;
        x = 1;          y = 1;          z = 1;
        xInc = 0.0;     yInc = -0.1;    zInc = 0.0;
}

/* Change coordonate system such that :
 * p1(x1,y1,z1) is the new origin
 * the vector v define by p1 et p2(x2,y2,z2) is the new Z-axis */
void alignZaxisNoRot(float x1, float y1, float z1, 
				float x2,float y2, float z2) {


	/* vector v = p2-p1 */
	float vx = x2-x1;
	float vy = y2-y1;
	float vz = z2-z1;
	
	// handle the degenerate case of z1 == z2 with an approximation
	if(vz == 0)
		vz = .0001;
	
	float v = sqrt( vx*vx + vy*vy + vz*vz );

	/* Compute the angle between vector v and the old z-axis */
	float ax = 57.2957795*acos( vz/v );
	if ( vz < 0.0 )
		ax = -ax;

	/* Compute the vector v^w with w the projection of v on (xOy) */
	float rx = -vy*vz;
	float ry = vx*vz;

	
	/* Changement of coordinate system */
	glTranslatef( x1,y1,z1 );
	glRotatef(ax, rx, ry, 0.0);
}


void Diver::draw() {
	

	glPushMatrix();

//        alignZaxisNoRot( 0,0,0,
//                    2,1,1);
        
        
	glRotated(-90, 1, 0, 0); // Le bonhomme est allongé
	glTranslatef(0, 0, cuisse + tibiat+main); // On fait le haut du corps

	glColor3fv (bodyc);
	gluCylinder(gluNewQuadric(), tronc/5, tronc/5, tronc , 10, 10);

	glPushMatrix();
	glTranslatef(0, 0, tronc); // On fait le haut du corps
	glColor3fv (skinc);

	gluCylinder(gluNewQuadric(), tronc/5, tronc/10, cou, 10, 10);
	glPushMatrix(); // La tete
	glTranslatef(0, 0, cou+tete/2);

	gluSphere(gluNewQuadric(), tete, 10, 10);


	glPopMatrix();// Fin haut du corps

	double ecart_bras_epaule = 120;// ecartement bras épaule
	double ecart_bras_avant_bras = 60;// ecartement bras épaule

	glPushMatrix(); // Debut mouvement bras;

	glRotated(angle_bras_mv, 1, 0, 0);

	glPushMatrix(); // un bras 1
	glRotated(ecart_bras_epaule, 0, 1, 0);
	glColor3fv (bodyc);
	gluCylinder(gluNewQuadric(), bras/8, bras/10, bras , 10, 10);
	glTranslatef(0, 0, bras);

	glRotated(ecart_bras_avant_bras, 0, 1, 0); 
	gluCylinder(gluNewQuadric(), bras/10, avant_bras/10, avant_bras, 10, 10);
	glTranslatef(0, 0, bras);
	glColor3fv (skinc);
	gluSphere(gluNewQuadric(), main, 10, 10); // Une main

	glPopMatrix(); // Fin bras 1


	glPushMatrix(); // un bras 2
	glRotated(-ecart_bras_epaule, 0, 1, 0);
	glColor3fv (bodyc);
	gluCylinder(gluNewQuadric(), bras/8, bras/10, bras , 10, 10);
	glTranslatef(0, 0, bras);

	glRotated(ecart_bras_avant_bras, 0, -1, 0); 
	gluCylinder(gluNewQuadric(), bras/10, avant_bras/10, avant_bras, 10, 10);
	glTranslatef(0, 0, bras);
	glColor3fv (skinc);
	gluSphere(gluNewQuadric(), main, 10, 10); // Une main

	glPopMatrix(); // Fin bras 2

	glPopMatrix(); // Fin mouvement bras;

	glPopMatrix(); // retour au bas du corps...

	double ecart_jambe = 15; // demi écartement des jambes

	glPushMatrix(); // debut jambe 1
	glRotated(180-ecart_jambe, 0, 1, 0);
	glColor3fv (legc);   

	gluCylinder(gluNewQuadric(), cuisse/3, cuisse/4, cuisse , 10, 10);
	glTranslatef(0, 0, cuisse);
	glRotated(5, 0, 1, 0);
	gluCylinder(gluNewQuadric(), cuisse/4, tibiat/4, tibiat , 10, 10);
	glTranslatef(0, 0, tibiat);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	glColor3fv (footc);
	gluCylinder(gluNewQuadric(), pied/4, pied/6, pied , 10, 10);


	glPopMatrix(); // fin jambe 1


	glPushMatrix(); // debut jambe 2
	glColor3fv (legc);
	glRotated(180+ecart_jambe, 0, 1, 0);
	gluCylinder(gluNewQuadric(), cuisse/3, cuisse/4, cuisse , 10, 10);
	glTranslatef(0, 0, cuisse);
	glRotated(-5, 0, 1, 0);
	gluCylinder(gluNewQuadric(), cuisse/4, tibiat/4, tibiat , 10, 10);
	glTranslatef(0, 0, tibiat);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	glColor3fv (footc);
	gluCylinder(gluNewQuadric(), pied/4, pied/6, pied , 10, 10);
 

	glPopMatrix(); // fin jambe 2



	glPopMatrix(); // Retour à rien du tout...
}