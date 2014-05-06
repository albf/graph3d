/*
 * Main GL viewer class, based on the QGLViewer library.
 * 
 * QGLViewer is a Qt-based viewer, which provides an OpenGL rendering
 * context and GUI event management.
 * The documentation of the QGLViewer library can be found at the following 
 * url: http://www.libqglviewer.com
 */
#pragma once

#ifndef _VIEWER_
#define _VIEWER_

#include <QGLViewer/qglviewer.h>
#include <list>
#include "cam.h"
#include "bubble.h"
#include "diver.h"
#include "pacMan.h"
//#include <QWidget>

using namespace std;

class Renderable;

class Viewer : public QGLViewer
{
	public :
		Viewer();
		virtual ~Viewer();
		void addRenderable(Renderable *r);
                void resizeWindow(int w, int h);
                Cam camera;
                	
        	static GLfloat position1[4];
                static GLfloat direction1[4];
            	static GLfloat spotAngle;
                static GLfloat position0[4];
                
                // Bubbles Variables
                int time;
                int bubble_frequency;
                float bubble_space;

/* Scene methods */
	protected :
		/// List of the scene objects, to render, animate, ...
		list<Renderable *> renderableList;
		
		/// Create the scene and initializes rendering parameters
		virtual void init();
		
		/// Draw every objects of the scene
		virtual void draw();


/* Viewing parameters */
	protected :
		bool toogleWireframe;
		bool toogleLight;
                int width, height;
                
                /// Animate every objects of the scene
		virtual void animate();

		/// Handle keyboard events specifically
		virtual void keyPressEvent(QKeyEvent *e);

		/// Handle keyboard events specifically
		virtual void mouseMoveEvent(QMouseEvent *e);
		
		/// Draw every objects of the scene
		virtual QString helpString() const;
                
                void timerEvent(QTimerEvent *e);
                
                void clear();
};

#endif
