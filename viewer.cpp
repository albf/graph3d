#include <QKeyEvent>

#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "viewer.h"
#include "renderable.h"
#include <iostream>

using namespace std;

Viewer::Viewer() {
}

Viewer::~Viewer()
{
	list<Renderable *>::iterator it;
	for (it = renderableList.begin(); it != renderableList.end(); ++it) {
 		delete(*it);
	}
	renderableList.clear();
}

void Viewer::addRenderable(Renderable *r)
{
        renderableList.push_back(r);
}

void Viewer::init()
{
        // glut initialisation (mandatory) 
        int dum;
  	glutInit(&dum, NULL);

	//=== VIEWING PARAMETERS
	restoreStateFromFile();   // Restore previous viewer state.

	toogleWireframe = false;  // filled faces
	toogleLight = true;       // light on
	//help();                   // display help

	if (toogleLight == true)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
	
	//setSceneRadius(0.0f);
        //resizeWindow(50, 50);
        camera.reset();
        camera.position();
   
	list<Renderable *>::iterator it;
	for (it = renderableList.begin(); it != renderableList.end(); ++it) {
	        (*it)->init(*this);
	}
        
        // Turn on timer, each 1000 ms timerEvent will be called
        startTimer(1000);
}

// Timed event, called at the time defined in viewer::init() functio.)
void Viewer::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    animate();
}

void Viewer::draw()
{  
	// draw every objects in renderableList
	list<Renderable *>::iterator it;
	for(it = renderableList.begin(); it != renderableList.end(); ++it) {
		(*it)->draw();
	}
}


void Viewer::animate()
{
    cout << "animate " << endl;
	// animate every objects in renderableList
	list<Renderable *>::iterator it;
	for(it = renderableList.begin(); it != renderableList.end(); ++it) {
		(*it)->animate();
	}
	
	// this code might change if some rendered objets (stored as
	// attributes) need to be specifically updated with common
	// attributes, like real CPU time (?)
}


void Viewer::mouseMoveEvent(QMouseEvent *e)
{
	// all renderables may respond to key events
	list<Renderable *>::iterator it;
	for(it = renderableList.begin(); it != renderableList.end(); ++it) {
	  (*it)->mouseMoveEvent(e, *this);
	}
	
	// default QGLViewer behaviour
	QGLViewer::mouseMoveEvent(e);
	updateGL();
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
	// Get event modifiers key
	const Qt::KeyboardModifiers modifiers = e->modifiers();

	// all renderables may respond to key events
	list<Renderable *>::iterator it;
	for(it = renderableList.begin(); it != renderableList.end(); ++it) {
	  (*it)->keyPressEvent(e, *this);
	}

	if ((e->key()==Qt::Key_W) && (modifiers==Qt::NoButton)) {
	// events with modifiers: CTRL+W, ALT+W, ... to handle separately
		toogleWireframe = !toogleWireframe;
		if (toogleWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else if ((e->key()==Qt::Key_L) && (modifiers==Qt::NoButton)) {
		toogleLight = !toogleLight;
		if (toogleLight == true)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);       
	// ... and so on with all events to handle here!

	} else {
		// if the event is not handled here, process it as default
		QGLViewer::keyPressEvent(e);
	}
	updateGL();
}

/* void setupViewVolume(void)
{
	// work out the aspect ratio for width and height
	//GLfloat aspect = (GLfloat)1024 / (GLfloat)height;
    GLfloat aspect = 1;
	//GLfloat iaspect = (GLfloat)height / (GLfloat)width;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(-45.0f, 1.0f, 1.0f, 250.0f);
	
	glMatrixMode(GL_MODELVIEW);
} */

void Viewer::resizeWindow(int w, int h) {
	glViewport(0, 0, w, h);
        //width = w;
	//height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	
	glMatrixMode(GL_MODELVIEW);
}



QString Viewer::helpString() const
{
	// Some usefull hints...
	QString text("<h2>V i e w e r</h2>");
	text += "Use the mouse to move the camera around the object. ";
	text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
	text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
	text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
	text += "Simply press the function key again to restore it. Several keyFrames define a ";
	text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
	text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
	text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
	text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
	text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
	text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
	text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
	text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
	text += "Press <b>Escape</b> to exit the viewer.";
	return text;
}

