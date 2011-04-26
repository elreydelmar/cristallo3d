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

void action_activer_retro(int active)
{
    if(active)
        MessageBox(NULL,"Retro actif","Camera",MB_OK);
    else
        MessageBox(NULL,"Retro inactif","Camera",MB_OK);
}

double conversion_slider_edit(int slider, double min, double max)
{
    double x = ((double)slider)/100;
    return ((max - min)*x*x+min);
}

void action_update_edit(HWND handle)
{
    char chaine [10];
    chaine[0] = sizeof(chaine);
    if(!SendMessage(handle, EM_GETLINE, 0, (LPARAM)chaine))
        return;
    int i=0;
    int connerie = 0;
    int virgule = 0;
    while(chaine[i] != 0)
    {
        if(!(chaine[i] >= '0' && chaine[i]<='9') && chaine[i]!=',' && chaine[i]!='.')
            connerie = 1;
        if(chaine[i] == ',' || chaine[i] =='.')
        {
            connerie = virgule;
            virgule = 1;
        }
        if(connerie)
        {
            chaine[i] = 0;
            SendMessage(handle, WM_SETTEXT, 1, (LPARAM)chaine);
            return;
        }
        i++;
    }
}

void action_change_edit(HWND hEdit, HWND hSlider, int priorite)
{
    static int autre_fait = 0;

    if(priorite == 1) // edit change
    {
        autre_fait = 1;
        // On change le trackbar


    }
}

void action_aide(HWND handle)
{
    MessageBox(handle,"Aide disponible bientôt","Aide",MB_OK);
}
