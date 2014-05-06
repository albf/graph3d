#ifndef _RENDERABLE_
#define _RENDERABLE_
#include <QKeyEvent>

#include <iostream>
#include <stdio.h>
#include "math.h"

#define PI 3.14159
#define FOV_RADIUS 3           // Radius of field of view
#define FOV_ANGLE 110          // Radius of field of view angle

class Viewer;

/**
 * General interface of renderable objetcs, that can be displayed
 * in the Viewer class.
 * It just defines three methods to override in child classes to
 * initialize, draw and animate a renderable objetc.
 */
class Renderable {
public:
    /// Virtual destructor (mandatory!)

    virtual ~Renderable() {
    };

    /** 
     * Initializes a Renderable objet before it is draw.
     * Default behavior: nothing is done.
     */
    virtual void init(Viewer&) {
    };

    /** 
     * Draw a Renderable object.
     * This pure virtual method must be overriden if child classes.
     */
    virtual void draw() = 0;

    /** 
     * Animate an object. This method is invoked before each call of draw().
     * Default behavior: nothing is done.
     */
    virtual void animate() {
    };

    /** 
     * Objects can respond to key events.
     * Default behavior: nothing is done.
     */
    virtual void keyPressEvent(QKeyEvent*, Viewer&) {
    };

    /** 
     * Objects can respond to mouse events.
     * Default behavior: nothing is done.
     */
    virtual void mouseMoveEvent(QMouseEvent*, Viewer&) {
    };

    float xcp, ycp, zcp; // Variables for cross-product
    float x,y,z;                    // For Movement
    float xInc, yInc, zInc;         // Incremet of object

    void getCrossProduct(float x, float y, float z, float a, float b, float c);
    float getAngle(float x, float y, float z, float a, float b, float c);
    void printXYZ(void);
    float vectorDistance(float x, float y, float z);
    float deg2rad( float deg ) { return deg * PI/ 180.0; }
    
    void setPos(float nx, float ny, float nz) {
        x=nx; y=ny; z=nz;
    }
    
    void setSpeed(float nx, float ny, float nz) {
        xInc=nx; yInc=ny; zInc=nz;
    }

};

#endif

