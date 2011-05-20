#include "evenement.h"
#include "GLbasic.h"
#include "affichage_maille.h"

extern EventStatus* event_status;

int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,LPSTR lignesDeCommande, int modeDAffichage)
{

    // Creation de la fenetre
    create_fenetre(cetteInstance);
    InitGL();

    while (recuperer_evenement())
    {
        traiter_evenement();

        display();
        drawscene();
        afficher_dessin();

        update_gl(); // glut
    }

    // Destruction de la fenetre
    delete_fenetre();

    return g_fenetre->message.wParam;

}
