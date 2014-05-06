#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif  

#include "seaFloor.h"

static GLuint gridTex;
static GLubyte* grid;

seaFloor::seaFloor() {
    x = 0;
    y = 0;
    z = 0;
    i=0;
}

void seaFloor::init(Viewer &v) {
     /* read in image for texture */
    grid = readPPMfile("seafloor.ppm");
    /* create a texture object */
    glGenTextures(1, &gridTex);
    /* make it the current texture */
    glBindTexture(GL_TEXTURE_2D, gridTex);
    /* make it wrap around */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    /* make it filter nicely */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    /* and put the image data into the texure object */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, grid);
}

void seaFloor::draw(void) {
    
 //   i++;
    glPushMatrix();
    /* turn on texture mapping and use the texture object created at initialization */
    glRotatef(90,1,0,0);
    glTranslatef(0,0,5);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, gridTex);

    /* texture coordinates place 5x5 copies of the texture on the rectangle */
    glBegin(GL_QUADS);
    glTexCoord2f(-7.0, -7.0);
    glVertex3f(x - 35.0, y - 35.0, 0.0);
    glTexCoord2f(-7.0, 7.0);
    glVertex3f(x - 35.0, y + 35.0, 0.0);
    glTexCoord2f(7.0, 7.0);
    glVertex3f(x + 35.0, y + 35.0, 0.0);
    glTexCoord2f(7.0, -7.0);
    glVertex3f(x + 35.0, y - 35.0, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

GLubyte* seaFloor::readPPMfile(char* filename) {
  FILE* input;
  int w,h,max,i,j,k;
  char rgb[3];
  GLubyte* vol;
  char buffer[200]; 

  if ((input = fopen(filename,"r")) == NULL) {
    fprintf(stderr,"Cannot open file %s \n",filename);
    exit(1);
  }
  /* read a line of input */
  fgets(buffer,200,input);
  if (strncmp(buffer,"P6",2) != 0) {
    fprintf(stderr,"%s is not a binary PPM file \n",filename);
    exit(1);
  }

  /* get second line, ignoring comments */
  do {
    fgets(buffer,200,input);
  } while (strncmp(buffer,"#",1) == 0);

  if (sscanf(buffer,"%d %d",&w,&h) != 2) {
    fprintf(stderr,"can't read sizes! \n");
    exit(1);
  }

  /* third line, ignoring comments */
  do {
    fgets(buffer,200,input);
  } while (strncmp(buffer,"#",1) == 0);

  if (sscanf(buffer,"%d",&max) != 1) {
    fprintf(stderr,"what about max size? \n");
    exit(1);
  }

  fprintf(stderr,"reading %d columns %d rows \n",w,h);

  vol = (GLubyte*) malloc(w*h*3*sizeof(GLubyte));
  for (i=h-1; i>=0; i--) {
    for (j=0; j<w; j++) {
      fread(rgb,sizeof(char),3,input);
      for (k=0; k<3; k++)
	*(vol+i*w*3+j*3+k) = (GLubyte) rgb[k];
    }
  }

  return(vol);
}