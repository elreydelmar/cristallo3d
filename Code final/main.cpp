#include "evenement.h"
#include "GLbasic.h"
#include "affichage_maille.h"

extern EventStatus* event_status;

int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,LPSTR lignesDeCommande, int modeDAffichage)
{
    // Creation de la fenetre
    create_fenetre(cetteInstance);

    while (recuperer_evenement())
    {
        traiter_evenement();

        display();
        drawscene();
        if(event_status!= NULL && event_status->maille != NULL)
            afficher_dessin();

        update_gl();
    }

    // Destruction de la fenetre
    delete_fenetre();

    return g_fenetre->message.wParam;

}
