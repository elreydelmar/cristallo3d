#include "evenement.h"

EventStatus* event_status = NULL;

LRESULT CALLBACK evenement(HWND fenetrePrincipale, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_COMMAND:
            evenement_bouton(fenetrePrincipale,message,wParam,lParam);
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

// Controle de event status

void init_event_status()
{
    if(event_status == NULL)
    {
        event_status = (EventStatus*) malloc(sizeof(EventStatus));
    }
}

void delete_event_status()
{
    if(event_status != NULL)
    {
        free(event_status);
        event_status = NULL;
    }
}

void evenement_bouton(HWND fenetrePrincipale, UINT message, WPARAM wParam, LPARAM lParam)
{
    // On fait un switch du bouton
     UINT id=LOWORD(wParam);

     switch(id)
     {
        case ID_HELP :
            MessageBox(fenetrePrincipale,"Aide disponible bientôt","",MB_OK);
        break;

        default :
            break;
     }
}
