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
