#include "evenement.h"
#include "GLbasic.h"



void display(void);
void drawscene();

int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,LPSTR lignesDeCommande, int modeDAffichage)
{
    // Creation de la fenetre
    create_fenetre(cetteInstance);
    InitGL();

    while (recuperer_evenement())
    {
        traiter_evenement();
        display();
/*
        // matrix + glclear

        nouveau_dessin();
        set_camera();

        //drawscene
        dessiner_repere(1);
        sample3d();
        afficher_dessin();

        //glut
        update_gl();
    */
    }

    // Destruction de la fenetre
    delete_fenetre();

    return g_fenetre->message.wParam;
}




void display(void)
{
    double IOD =0.3;
    double screenZ = 10;
    double depthZ = -10.0;

			//glStencilFunc(GL_ALWAYS,1,1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, HEIGHT/(WIDTH-WIDTH_MENU), 0.1, 1000);
  glDrawBuffer(GL_BACK);                                   //draw into both back buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      //clear color and depth buffers

  glDrawBuffer(GL_BACK_LEFT);                              //draw into back left buffer
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();                                      //reset modelview matrix
  gluLookAt(-IOD/2,                                        //set camera position  x=-IOD/2
            0.5,                                           //                     y=0.0
            -screenZ,                                           //                     z=0.0
            0.0,                                           //set camera "look at" x=0.0
            0.0,                                           //                     y=0.0
            0.0,                                        //                     z=screenplane
            0.0,                                           //set camera up vector x=0.0
            1.0,                                           //                     y=1.0
            0.0);                                          //                     z=0.0

  glPushMatrix();
  {
    glTranslatef(0.0, 0.0, depthZ);
    glColorMask(1,0,0,1);                        //translate to screenplane
    drawscene();
  }
  glPopMatrix();

  glDrawBuffer(GL_BACK_RIGHT);                             //draw into back right buffer
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();                                        //reset modelview matrix
  gluLookAt(IOD/2, 0.5, -screenZ, 0.0, 0.0, 0,            //as for left buffer with camera position at:
            0.0, 1.0, 0.0);                                //                     (IOD/2, 0.0, 0.0)

  glPushMatrix();
  {
    glTranslatef(0.0, 0.0, depthZ);                        //translate to screenplane
    glColorMask(0,1,1,1);
    drawscene();
  }
  glPopMatrix();

        update_gl();

}


void drawscene()
{

        dessiner_repere(1);
        sample3d();
        afficher_dessin();
}
