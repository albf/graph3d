#include "cam.h"

/// Default Constructor. Initialises defaults.

Cam::Cam() {
    reset();
}

/// Default destructor.

Cam::~Cam() {
}

/// Resets the camera position to default position and tilt

void Cam::reset(void) {
    distance = -50.0f;
    verticalTilt = -30.0f;
    horizontalAngle = 90.0f;
}

/// Positions the camera at the required place and rotation
/// Zoom and spin is done by translate/rotate

void Cam::position(void) {
    glTranslatef(0.0f, 0.0f, this->distance);
    glRotatef(this->verticalTilt, 1.0f, 0.0f, 0.0f);
    glRotatef(this->horizontalAngle, 0.0f, 1.0f, 0.0f);
}
/// Decrements the distance to origin (zoom in)

void Cam::dec(void) {
    distance--;
}

/// Incrementes the distance to origin (zoom out)

void Cam::inc(void) {
    distance++;
}

/// Adjusts the camera rotation around the Y axis

void Cam::clockwise(void) {
    horizontalAngle++;
}

/// Adjusts the camera rotation around the Y axis

void Cam::anticlockwise(void) {
    horizontalAngle--;
}

/// Adjusts the camera rotation around the X axis
/// the angle is locked if it gets above 0 degrees

void Cam::tiltup(void) {
    if (verticalTilt < 0)
        verticalTilt++;
}

/// Adjusts the camera rotation around the X axis
/// The angle is locked if it gets greate than 90 degrees

void Cam::tiltdown(void) {
    if (verticalTilt > -90)
        verticalTilt--;
}