#include <qapplication.h>
#include "viewer.h"
#include "lightsMaterials.h"
#include "fishA.h"
#include "fishB.h"
#include "crab.h"
#include "seaFloor.h"
#include "unistd.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    // Read command lines arguments.
    QApplication application(argc, argv);
    srand(time(NULL));
    float x, y, z;
    int i, j;

    // Instantiate the viewer.
    Viewer viewer;

    // build your scene here

    // add sea floor
    viewer.addRenderable(new seaFloor());


    //viewer.addRenderable(new LightsMaterials());
    fishA fish;
    fish.printXYZ();

    // #1 Group of FishB
    x = 0;
    y = 0;
    z = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            viewer.addRenderable(new fishB(x + (i * 1.2), y + j, z,
                0.1, 0, 0,
                0.8, 0.2, 0.2));

    // #2 Group of FishB
    x = -5;
    y = -1;
    z = 17;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++)
            viewer.addRenderable(new fishB(x - (3.2 * 0.05 * i / 0.17), y + j + (3.2 * 0.07 * i / 0.17), z - (3.2 * 0.05 * i / 0.17),
                -0.05, 0.07, -0.05,
                0.2, 0.8, 0.2));


    // #3 Some Crabs
    viewer.addRenderable(new crab());
    viewer.addRenderable(new crab(5, 5, 0.04, 0.02));
    viewer.addRenderable(new crab(-10, -5, -0.02, 0.07));

    // #4 Group of FishB
    x = -5;
    y = 1;
    z = 1;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 2; j++)
            viewer.addRenderable(new fishB(x + (i * (1.3)), y + j, z,
                0.3, 0.05, 0.01,
                -0.8, 0.2, 0.2));


    // #5 Group of FishB
    x = -10;
    y = -12;
    z = -3;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            viewer.addRenderable(new fishB(x + (i * (1.2)), y + j, z,
                0.1, 0, 0,
                0.8, 0.2, 0.2));

    
    // #6 Different Fish
    viewer.addRenderable(&fish);

    // #7 Diver and Bubbles : added inside viewer, following lines are for debug only
    
    //viewer.addRenderable(new Diver(5));
    //viewer.addRenderable(new Bubble(0, 0, 20, 0.5, 0.1));
    
    // #8 Pacman
    // added in the viewer, after some time has passed    
    
    
    // Make the viewer window visible on screen.
    viewer.setWindowTitle("Graphic 3D Projet");
    viewer.show();
    viewer.resize(800, 800);

    // Run main loop.
    return application.exec();
}