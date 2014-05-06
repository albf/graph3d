#include "cam.h"

// Default Constructor. Initialises defaults.
Cam::Cam() {
    reset();
}

// Default destructor.
Cam::~Cam() {
}

// Resets the camera position to default position and tilt
void Cam::reset(void) {
    distance=35;
    verticalTilt=0;
    horizontalAngle=-5;
    
/*    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(0,0,0,0,0,0);      // Left=-2, Right=2, Bottom=-2, Top=2, Near=5, Far=9
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); */
}
    
// Positions the camera at the required place and rotation
// Zoom and spin is done by translate/rotate
void Cam::position(void) {
    
    printCamValues(); // Debug
  
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    
    glLoadIdentity();
    gluLookAt(0.0, 0.0, distance,
            0.0, horizontalAngle, -1.0,
            0.0, 1.0+verticalTilt, 0.0);

    //distance = distance + 0.1;    // debug
    //verticalTilt = verticalTilt+ 0.1;
    //horizontalAngle=horizontalAngle+0.1;
}

// Decrements the distance to origin (zoom in)
void Cam::dec(float value) {
    distance-=value;
}

// Increments the distance to origin (zoom out)
void Cam::inc(float value) {
    distance+=value;
}

// Adjusts the camera rotation around the Y axis
void Cam::clockwise(void) {
    horizontalAngle++;
}

// Adjusts the camera rotation around the Y axis
void Cam::anticlockwise(void) {
    horizontalAngle--;
}

// Adjusts the camera rotation around the X axis
// the angle is locked if it gets above 0 degrees
void Cam::tiltup(void) {
    if (verticalTilt < 0)
        verticalTilt++;
}

// Adjusts the camera rotation around the X axis
// The angle is locked if it gets greate than 90 degrees
void Cam::tiltdown(void) {
    if (verticalTilt > -90)
        verticalTilt--;
}

void Cam::printCamValues(void) {
    std::cout << "verticalTilt:     " << verticalTilt << std::endl;
    std::cout << "horizontalAngle:  " << horizontalAngle << std::endl;
    std::cout << "distance:         " << distance << std::endl << std::endl;    
}