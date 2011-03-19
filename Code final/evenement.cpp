#include "evenement.h"

LRESULT CALLBACK evenement(HWND fenetrePrincipale, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_SIZE:
		{
		    redimensionner(fenetrePrincipale, LOWORD(lParam),HIWORD(lParam));
		    update_gl();
			return 0;
		}

        default:
            return DefWindowProc(fenetrePrincipale, message, wParam, lParam);
    }
}

int recuperer_evenement()
{
    return GetMessage(&(g_fenetre->message), NULL, 0, 0);
}

void traiter_evenement()
{
    TranslateMessage(&(g_fenetre->message));
    DispatchMessage(&(g_fenetre->message));
}

/*
void creer_boutons(HWND hParent, HINSTANCE instance)
{

        // FreeFly ou TrackBall
        creer_radiobouton("FreeFly", "TrackBall", ID_FREEFLY, ID_TRACKBALL, Cadre_camera, instance, pos);
        // Anaglyphe ou non
        pos.y += pos.h + Y_ESPACE;
        creer_check_box("Anaglyphe", ID_ANAGLYPHE, Cadre_camera, instance, pos);

        // Slider


    {
        HWND hControle;
        // Modèle de bouton ... 4 types : BS_GROUPBOX, BS_PUSHBUTTON, BS_RADIOBUTTON (carré), BS_CHECKBOX (rond)
        hControle=CreateWindow(
            "BUTTON",
            "Button 1",
            WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, //d'autres flags (cad options) possibles avec |BS_(...) / e.g.:(...)|BS_PUSHBUTTON|BS_MULTILINE,
            10+10,10+20, //coordonnées de l'origine du rectange (x, y)
            100,20,  //longueur et hauteur du rectangle
            fenetre->handle,
            (HMENU)ID_PUSHBUTTON_1, //ID du bouton, sert à le linker à une fonctionnalité ... à #define au préalable
            instance,
            NULL);

    }*/
    /*
    HWND Cadre_maille=CreateWindow(
        "BUTTON",
        "Maille",
        WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
        ALINEA_MENU,Y_MAILLE,
        WIDTH_MENU,HEIGHT_MAILLE,
        hParent,
        NULL,
        instance,
        NULL);


            HWND Cadre_valeur=CreateWindow(
        "BUTTON",
        "Mise en valeur",
        WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
        ALINEA_MENU,Y_VALEUR,
        WIDTH_MENU,HEIGHT_VALEUR,
        hParent,
        NULL,
        instance,
        NULL);
    {

    }
}
*/
