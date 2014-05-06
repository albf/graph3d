#ifndef DIVER_H_
#define DIVER_H_


#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <QGLViewer/vec.h>
#include "renderable.h"

class Diver : public Renderable {
	
private:
	// Définition des tailles

	double ratio;

	double corps;
	double tete;
	double main;
	double pied;
	double cou;
	double avant_bras;
	double bras;
	double tronc;
	double tibiat;
	double cuisse;

	float bodyc[3];
	float skinc[3];
	float legc[3];
	float footc[3];

	qglviewer::Vec direction;

	qglviewer::Vec Vtete;
	qglviewer::Vec tronc_bas;
	qglviewer::Vec tronc_haut;

	qglviewer::Vec epaule_droite;
	qglviewer::Vec coude_droit;
	qglviewer::Vec main_droite;
	qglviewer::Vec hanche_droite;
	qglviewer::Vec genoux_droit;
	qglviewer::Vec cheville_droite;


	qglviewer::Vec PositionPred[100];
	qglviewer::Vec VelPred[100];


	double angle_bras_mv;
	
	

public:
	Diver(double taille);

	void animer(double dt);

	void majPosBras(double val);

	void draw();

	void majPos(qglviewer::Vec newPos);

	qglviewer::Vec getPosSmooth();

	void majVel(qglviewer::Vec newVel);

	qglviewer::Vec getVelSmooth();
	

};

#endif
