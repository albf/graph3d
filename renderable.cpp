#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "renderable.h"

void Renderable::getCrossProduct(float x, float y, float z, float a, float b, float c) {
    xcp = (y * c)-(z * b);
    ycp = (z * a)-(x * c);
    zcp = (x * b)-(y * a);
}

float Renderable::getAngle(float x, float y, float z, float a, float b, float c) {
    float dot_product = (x*a) + (y*b) + (z*c);
    float div = vectorDistance(x,y,z)*vectorDistance(a,b,c);
    float arc = (float) acos(dot_product/div);
    return arc* 180.0 / PI;
}

void Renderable::printXYZ(void) {
    std::cout << "x " << x << std::endl;
    std::cout << "y " << y << std::endl;
    std::cout << "z " << z << std::endl;
    std::cout << std::endl;
}

float Renderable::vectorDistance(float x, float y, float z) {
    return (float)sqrt((x*x)+(y*y)+(z*z));
}