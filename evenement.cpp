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
			return 0;
		}

        default:
            return DefWindowProc(fenetrePrincipale, message, wParam, lParam);
    }
}

int recuperer_evenement(Fenetre* fenetre)
{
    return GetMessage(&(fenetre->message), NULL, 0, 0);
}

void traiter_evenement(Fenetre* fenetre)
{
    TranslateMessage(&(fenetre->message));
    DispatchMessage(&(fenetre->message));
}

void redimensionner(HWND fenetre, int width, int height)
{
    HWND handle_gl = GetWindow(fenetre, GW_CHILD);

    // On regarde l'agrandissement
    int new_x = width - WIDTH_COLONNE;

    // On redimensionne la fenetre opengl
    MoveWindow(handle_gl, 0, 0, new_x, height, TRUE);
    redimensionner_gl(new_x, height);
}
