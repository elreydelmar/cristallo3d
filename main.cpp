#include "fenetre.h"

int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,LPSTR lignesDeCommande, int modeDAffichage)
{
    Fenetre fenetre;
    Contexte_GL* contexte_opengl = NULL;

    init_fenetre(&fenetre, cetteInstance, &contexte_opengl);

    afficher_fenetre(&fenetre, modeDAffichage);
    update_fenetre(&fenetre);

    while (recuperer_evenement(&fenetre))
    {
        traiter_evenement(&fenetre);

        sample_dessin_3d();

        update_gl(contexte_opengl);
    }

    end_fenetre(&fenetre, contexte_opengl);

    return fenetre.message.wParam;
}
