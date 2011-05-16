#include "evenement.h"
#include "GLbasic.h"


int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,LPSTR lignesDeCommande, int modeDAffichage)
{
    // Creation de la fenetre
    create_fenetre(cetteInstance);
    InitGL();

    while (recuperer_evenement())
    {
        traiter_evenement();

    // matrix + glClear
        nouveau_dessin();
        set_camera();

    // drawscene
        dessiner_repere(1);
        sample3d();
        afficher_dessin();

        update_gl(); // glut
    }

    // Destruction de la fenetre
    delete_fenetre();

    return g_fenetre->message.wParam;
}
