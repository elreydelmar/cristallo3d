#include "debug.h"

void affiche_erreur (char* msg)
{
        MessageBox(NULL,
                   TEXT(msg),
                   TEXT("Debug"),
                   MB_OK);
}
