#include <qapplication.h>
#include "viewer.h"
#include "lightsMaterials.h"
#include "fishA.h"
#include "fishB.h"
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
    fishB fish;
    fish.printXYZ();
    
    fishA fish2;
    fish2.x=0;
    fish2.y=5;
    fish2.z=0;
    
    fishB fish3;
    fishB fish4;
    
    fish3.x=0;
    fish3.y=0;
    fish3.z=0;
    
    fish4.x=0;
    fish4.y=-1;
    fish4.z=0;
    
    viewer.addRenderable(&fish);
    viewer.addRenderable(&fish2);
    viewer.addRenderable(&fish3);
    viewer.addRenderable(&fish4);
    
   //fish.printXYZ();
        
    viewer.setWindowTitle("viewer");
    // Make the viewer window visible on screen.
    viewer.show();
    viewer.resize(800, 800);

    // Run main loop.
    return application.exec();
}