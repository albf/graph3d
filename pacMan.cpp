#include "pacMan.h"

static void drawHalfSphere(int lats, int longs, int sides);

pacMan::pacMan(float posx, float posy, float posz, float velx, float vely, float velz, float Nscale) {
    x = posx; y=posy; z=posz;
    xInc = velx; yInc = vely; zInc = velz;
    scale = Nscale;
    time=0;
    modeTime=0;
}

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

void pacMan::draw() {
    x += xInc;
    y += yInc;
    z += zInc;
    
    glColor4f(1, 1, 0, 1);
    
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);
    
    glPushMatrix(); // first side of the pacman
    glRotatef(-time*5,1,0,0);
    drawHalfSphere(80, 80, 1);
    
    glColor4f(0, 0, 0, 0.8);
    glTranslatef(-0.5,0.5,0.8);
    glScalef(0.75/scale, 0.75/scale, 0.75/scale);
    drawHalfSphere(80,80,2);
    
    glScalef(scale/0.75, scale/0.75, scale/0.75);
    glTranslatef(+1,0,0);
    glScalef(0.75/scale, 0.75/scale, 0.75/scale);
    drawHalfSphere(80,80,2);
            
    glPopMatrix(); // end of first side of pacman

    glColor4f(1, 1, 0, 1);
    glPushMatrix(); // second side of the pacman
    glRotatef(180,0,0,1);
    glRotatef(-time*5,1,0,0);
    drawHalfSphere(80, 80, 1);
    glPopMatrix(); // end of second side of pacman

    glPopMatrix();
}

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