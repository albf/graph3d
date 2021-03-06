#include "pacMan.h"

static void drawHalfSphere(int lats, int longs, int sides);

pacMan::pacMan(float posx, float posy, float posz, float velx, float vely, float velz, float Nscale) {
    x = posx; y=posy; z=posz;
    xInc = velx; yInc = vely; zInc = velz;
    scale = Nscale;
    time=0;
    modeTime=0;
}

// Just update the time, to know how to move the mouth
void pacMan::animate() {
    if(modeTime==0) {
        time++;
        if(time>15)
            modeTime=1;
    }
    else {
        time--;
        if(time==0)
            modeTime=0;
    }
}

// Draw function
void pacMan::draw() {
    x += xInc;  // update coordinates
    y += yInc;
    z += zInc;
    
    glColor4f(1, 1, 0, 1);  // yellow color
    
    glPushMatrix();
    
    glTranslatef(x, y, z);  // move pacman
    getCrossProduct(xInc, yInc, zInc, 0, 0, 1); // get cross product
    glRotatef(getAngle(xInc, yInc, zInc, 0, 0, 1), xcp, ycp, zcp); // rotate to look to where it is moving
    
    glScalef(scale, scale, scale);  // scale
    
    // first side of the pacman
    glPushMatrix(); 
    // First Half
    glRotatef(-time*5,1,0,0);   // rotation of the first side
    drawHalfSphere(80, 80, 1);  // draw it's first half
    
    // First Eye
    glColor4f(0, 0, 0, 0.8);    
    glTranslatef(-0.5,0.5,0.8); // go to the position
    glScalef(0.75/scale, 0.75/scale, 0.75/scale);
    drawHalfSphere(80,80,2);    // draw a full sphere this time
    
    // Second Eye
    glScalef(scale/0.75, scale/0.75, scale/0.75);
    glTranslatef(+1,0,0);   // go to the position
    glScalef(0.75/scale, 0.75/scale, 0.75/scale);
    drawHalfSphere(80,80,2);    // draw a full sphere thi time
            
    glPopMatrix(); // end of first side of pacman
    
    glColor4f(1, 1, 0, 1);
    glPushMatrix(); // second side of the pacman
    
    // Second Half
    glRotatef(180,0,0,1);
    glRotatef(-time*5,1,0,0);
    drawHalfSphere(80, 80, 1);
    glPopMatrix(); // end of second side of pacman

    glPopMatrix();
}

/* Draw half of sphere : Took TP1 and executed just half of the for-loop if sides=1,
 * or the full loop if sides=2 */
static void drawHalfSphere(int lats, int longs, int sides) {
        int i, j;
        for(i = 0; i <= lats; i++) {
                double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
                double z0  = sin(lat0);
                double zr0 =  cos(lat0);
        
                double lat1 = M_PI * (-0.5 + (double) i / lats);
                double z1 = sin(lat1);
                double zr1 = cos(lat1);

                glBegin(GL_QUAD_STRIP);
                for(j = 0; j <= sides*longs/2; j++) {
                        double lng = 2 * M_PI * (double) (j - 1) / longs;
                        double x = cos(lng);
                        double y = sin(lng);

                        glNormal3f(x * zr0, y * zr0, z0);
                        glVertex3f(x * zr0, y * zr0, z0);
                        glNormal3f(x * zr1, y * zr1, z1);
                        glVertex3f(x * zr1, y * zr1, z1);
                }
                glEnd();
        }
}