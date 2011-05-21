#include "anaglyphe.h"


void display_anaglyphe(Camera* camera, double ecartement_yeux)
{
    // Oeil rouge
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_BLEND);

    glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                                        //reset modelview matrix
    set_camera(-ecartement_yeux/2);

    drawscene();

    // Oeil cyan
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                                        //reset modelview matrix
    set_camera(+ecartement_yeux/2);

    drawscene();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Pour le glClear color buffer bit
}



