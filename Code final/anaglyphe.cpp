#include "anaglyphe.h"

//toed-in stereo

float depthZ = -1.0;                                      //depth of the object drawing

double fovy = 45;                                          //field of view in y-axis
double aspect = 640/480;  //screen aspect ratio
double nearZ = 3.0;                                        //near clipping plane
double farZ = 30.0;                                        //far clipping plane
double screenZ = 1;                                     //screen projection plane
double IOD = 0.05;                                          //intraocular distance


void display_anaglyphe(Camera* camera)
{
    glDrawBuffer(GL_BACK);                               //draw into both back buffers
  nouveau_dessin();      //clear color and depth buffers
    //glClear(GL_ACCUM_BUFFER_BIT);

  glDrawBuffer(GL_BACK_LEFT);                              //draw into back left buffer
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();                                        //reset modelview matrix
  gluLookAt(-IOD/2,                                        //set camera position  x=-IOD/2
            0,                                           //                     y=0.0
            screenZ,                                           //                     z=0.0
            0.0,                                           //set camera "look at" x=0.0
            0.0,                                           //                     y=0.0
            0,                                       //                     z=screenplane
            0.0,                                           //set camera up vector x=0.0
            1,                                           //                     y=1.0
            0);                                          //                     z=0.0

  glPushMatrix();
  {
    glTranslatef(0.0, 0.0, depthZ);                        //translate to screenplane
    drawscene();
  }
  glPopMatrix();


  glDrawBuffer(GL_BACK_RIGHT);                             //draw into back right buffer
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();                                        //reset modelview matrix
  gluLookAt(+IOD/2, 0, screenZ, 0.0, 0.0, 0,            //as for left buffer with camera position at:
            0.0, 1, 0);                                //                     (IOD/2, 0.0, 0.0)

  glPushMatrix();
  {
    glTranslatef(0.0, 0.0, depthZ);                        //translate to screenplane
    drawscene();
  }
  glPopMatrix();

}



