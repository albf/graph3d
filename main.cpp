#include <qapplication.h>
#include "viewer.h"
#include "lightsMaterials.h"
#include "fishA.h"
#include "unistd.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    // Read command lines arguments.
    QApplication application(argc,argv);
    srand(time(NULL));


    // Instantiate the viewer.
    Viewer viewer;

    // build your scene here
    //viewer.addRenderable(new LightsMaterials());
    fishA fish;
    fish.printXYZ();
    viewer.addRenderable(&fish);
    
        GLfloat x = (((GLfloat)rand() / (GLfloat)RAND_MAX) * 50) - 25;
	GLfloat z = (((GLfloat)rand() / (GLfloat)RAND_MAX) * 50) - 25;

	// the height is a bit different, differnt objects need a different
	// offset above the sea floor
       	GLfloat y = (((GLfloat)rand() / (GLfloat)RAND_MAX) * 25) - 26;

        //fish.x = x;
        //fish.y = y;
        //fish.z = z;
        
        fish.printXYZ();
        
    viewer.setWindowTitle("viewer");
    // Make the viewer window visible on screen.
    viewer.show();
    viewer.resize(800, 800);

    // Run main loop.
    return application.exec();
}