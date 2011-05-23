#include "anaglyphe.h"


void display_anaglyphe(Camera* camera, int retro, double distance_retro, double distance_ecran)
{
    double ecartement_yeux;
    if(retro)
    {
        if(distance_ecran > distance_retro)
            ecartement_yeux = 0.05*sqrt(distance_ecran-distance_retro);
        else
            ecartement_yeux =0;
    }
    else
        ecartement_yeux = 0.05*sqrt(distance_ecran);

    // Oeil rouge
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_BLEND);

    glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                                        //reset modelview matrix
    set_camera(g_fenetre->gl_width, g_fenetre->gl_height, -ecartement_yeux/2);

    drawscene();

    // Oeil cyan
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);

    glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                                        //reset modelview matrix
    set_camera(g_fenetre->gl_width, g_fenetre->gl_height,+ecartement_yeux/2);

    drawscene();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE); // Pour le glClear color buffer bit
}



