#include "evenement.h"
#include "GLbasic.h"


int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,LPSTR lignesDeCommande, int modeDAffichage)
{
    // Creation de la fenetre
    create_fenetre(cetteInstance);
    init_camera_de_merde();
    InitGL();

    while (recuperer_evenement())
    {
        traiter_evenement();
        nouveau_dessin();
        update_camera_de_merde();

        dessiner_repere(1);

        sample3d();

        afficher_dessin();
        update_gl();
    }

    // Destruction de la fenetre
    delete_fenetre();

    return g_fenetre->message.wParam;
}
