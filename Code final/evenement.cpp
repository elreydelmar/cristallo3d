#include "evenement.h"

EventStatus* event_status = NULL;

LRESULT CALLBACK evenement(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(handle != NULL)
    {
        int idFenetre = GetWindowLong(handle, GWL_USERDATA);

        if(idFenetre == 1)
        {
            return evenement_principale(handle, message, wParam, lParam);
        }
        else
        {
            return evenement_menu(handle, message, wParam, lParam);
        }
    }

    switch (message)
    {
        case WM_CREATE:
            return 0;

        default:
            return DefWindowProc(handle, message, wParam, lParam);
    }
}

LRESULT evenement_principale(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_SIZE:
        {
            redimensionner(handle, LOWORD(lParam),HIWORD(lParam));
            update_gl();
            return 0;
        }

        default:
            return DefWindowProc(handle, message, wParam, lParam);
    }
}

LRESULT evenement_menu(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {

        case WM_COMMAND:
            evenement_bouton(handle,message,wParam,lParam);
            return 0;

        default:
            return DefWindowProc(handle, message, wParam, lParam);
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

void evenement_bouton(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    // On fait un switch du bouton
    UINT id=LOWORD(wParam);

    switch(id)
    {
        case ID_FREEFLY : action_change_camera(0); break ;
        case ID_TRACKBALL : action_change_camera(1); break;
        case ID_ANAGLYPHE : action_change_anaglyphe(SendMessage(g_fenetre->anaglyphe, BM_GETCHECK, 0, 0) == BST_CHECKED); break;
        case ID_HELP : action_aide(handle); break;

        default :
            break;
    }
}
