#ifndef __CAMERA__
#define __CAMERA__

#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.14159

class Cam
{
private:
	GLfloat verticalTilt;
	GLfloat horizontalAngle;
	GLfloat distance;

public:
	Cam();	/// default constructor
	virtual ~Cam();	/// default destructor

	void reset(void);	/// resets the camera to default position
	void position(void);	/// sets up camera at current position
	void dec(void);	/// decreases distance to origin
	void inc(void);	/// increases distance to origin
	void clockwise(void);	/// rotate scene clockwise
	void anticlockwise(void);	/// rotate scene anticlockwise
	void tiltup(void);	/// tilts camera upwards
	void tiltdown(void);	/// tilts camera downwards
};

#endif
