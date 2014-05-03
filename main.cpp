#include <qapplication.h>
#include "viewer.h"
#include "lightsMaterials.h"
#include "fishA.h"
#include "unistd.h"
#include <iostream>

//Viewer viewer;
static bool init(int argc, char *argv[]); /// initialises the application
static void setupGL(void); /// initialises OpenGL
//static void animate(int type); /// animates the aquarium

using namespace std;

int main(int argc, char** argv) {
    // Read command lines arguments.
    QApplication application(argc,argv);

    //init(argc, argv);

    // Instantiate the viewer.
    Viewer viewer;

    // build your scene here
    //viewer.addRenderable(new LightsMaterials());
    //fishA fish1;
    viewer.addRenderable(new fishA());

    viewer.setWindowTitle("viewer");
    // Make the viewer window visible on screen.
    viewer.show();
    viewer.resize(800, 800);
    viewer.camera.position();

    viewer.show();
    viewer.camera.dec();
    viewer.camera.dec();
    viewer.camera.dec();
    viewer.camera.dec();
    viewer.camera.dec();
    cout << "ponto a" << endl;
    usleep(1000000);
    viewer.camera.position();
    cout << "ponto b" << endl;
    viewer.show();


    // Run main loop.
    return application.exec();
    //glutTimerFunc(50, animate, 0);
    //glutMainLoop();
    //return 0;
}

/*void animate(int type) {
    viewer.show();
    glutTimerFunc(25, animate, 0);

} */

/// Init GLUT and OpenGL

/*
 * Creates a window that is half the size of the screen
 * and then calls setupGL() to setup the initial OpenGL
 * environment.
 */
bool init(int argc, char *argv[]) {
    // initialise glut
    cout << "-- Initialising GLUT\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // setup our widnow now
    cout << "-- Creating window\n";
    glutCreateWindow("Aquarium Scene 3D");
    glutFullScreen();

    // initialise opengl initial state
    setupGL();

    return true;
}


/// Sets up the OpenGL state machine environment
/// All hints, culling, fog, light models, depth testing, polygon model
/// and blending are set up here

void setupGL(void) {
    cout << "-- Setting up OpenGL state\n";

    // blue green background colour
    glClearColor(0.0, 0.5, 0.55, 1.0);

    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // depth testing used on with less than testing
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    // setup  fog, but disable for now
    glDisable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    GLfloat fogColor[4] = {0.0f, 0.5f, 0.55f, 1.0f};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.0075);
    glHint(GL_FOG_HINT, GL_NICEST);

    // enable normalising of normals after scaling
    glEnable(GL_NORMALIZE);

    // setup lighting, but disable for nwo
    glDisable(GL_LIGHTING);
    GLfloat ambient[] = {0.1f, 0.1f, 0.1f, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    /*
     * The actual lights are defined in the Scene class
     */

    // set up line antialiasing
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // setup backface culling
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // choose nices perspective correction for textures
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
