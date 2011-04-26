#include "actions.h"

// Globales
extern Fenetre* g_fenetre;


void action_change_camera(int type)
{
    if(type)
        MessageBox(NULL,"Trackball","Camera",MB_OK);
    else
        MessageBox(NULL,"Freefly","Camera",MB_OK);
}

void action_change_anaglyphe(int checked)
{
    if(checked)
        MessageBox(NULL,"Anaglyphe","Camera",MB_OK);
    else
        MessageBox(NULL,"Pas Anaglyphe","Camera",MB_OK);
}

void action_aide(HWND handle)
{
    MessageBox(handle,"Aide disponible bientôt","Aide",MB_OK);
}
