#include "evenement.h"

int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,LPSTR lignesDeCommande, int modeDAffichage)
{
    // Creation de la fenetre
    create_fenetre(cetteInstance);


    while (recuperer_evenement())
    {
        traiter_evenement();

        sample_dessin_2d();

        update_gl();
    }

    // Destruction de la fenetre
    delete_fenetre();

    return g_fenetre->message.wParam;
}
