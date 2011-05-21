#include "anaglyphe.h"

//toed-in stereo

float depthZ = 0.0;                                      //depth of the object drawing
double screenZ = 1;                                     //screen projection plane
double IOD = 0.05;                                          //intraocular distance


void display_anaglyphe(Camera* camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);

    // set camera for blue eye, red will be filtered.
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
    set_camera();

    glPushMatrix();
    {
    //glTranslatef(0.0, 0.0, depthZ);                        //translate to screenplane
    drawscene();
    }
    glPopMatrix();


    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                                        //reset modelview matrix
    gluLookAt(+IOD/2, 0, screenZ, 0.0, 0.0, 0,            //as for left buffer with camera position at:
            0.0, 1, 0);                                //                     (IOD/2, 0.0, 0.0)
    set_camera();

    glPushMatrix();
    {
    //glTranslatef(0.0, 0.0, depthZ);                        //translate to screenplane
    drawscene();
    }
    glPopMatrix();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Pour le glClear color buffer bit
}



