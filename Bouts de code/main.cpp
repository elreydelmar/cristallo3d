#include "evenement.h"
#include "TestGL.h"





int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,LPSTR lignesDeCommande, int modeDAffichage)
{
    // Creation de la fenetre
    create_fenetre(cetteInstance);

    InitGL();
    while (recuperer_evenement())
    {
        traiter_evenement();

        nouveau_dessin();

        dessiner_repere(1);
        //dessiner_cylindre({0.1,0.1,1,8}, {250,0,0});
        Point P={1,0,1};
        Point Q={0,1,1};
        Ligne ligne={P,Q};
        dessiner_ligne({250,0,0},ligne,0.1);
        //Point Z=sub_pts (ligne.Q,ligne.P);
        //changerepere (ligne.P,Z);
        //dessiner_repere(1);

        /*dessiner_cube(0.5, {250,0,0}, 1);
        //dessiner_cylindre({0.1,0.1,1,10}, {250,0,0});
        dessiner_sphere({0.1,100,100},{250,0,0}, {0.25,0.25,0.25});
        dessiner_sphere({0.1,100,100},{250,0,0}, {-0.25,0.25,0.25});
        dessiner_sphere({0.1,100,100},{250,0,0}, {0.25,-0.25,0.25});
        dessiner_sphere({0.1,100,100},{250,0,0}, {0.25,0.25,-0.25});
        dessiner_sphere({0.1,100,100},{250,0,0}, {-0.25,-0.25,0.25});
        dessiner_sphere({0.1,100,100},{250,0,0}, {0.25,-0.25,-0.25});
        dessiner_sphere({0.1,100,100},{250,0,0}, {-0.25,0.25,-0.25});
        dessiner_sphere({0.1,100,100},{250,0,0}, {-0.25,-0.25,-0.25});*/
        glFlush();

        update_gl();
    }

    // Destruction de la fenetre
    delete_fenetre();

    return g_fenetre->message.wParam;
}
