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
    double x = ((double)slider)/100.;
    return ((max - min)*x*x+min);
}

int conversion_edit_slider(double edit, int imin, int imax, double min, double max)
{
    if(imin == imax)
        return imin;
    else
    {
        int middle = (imax - imin)/2 + imin;
        double calcul = conversion_slider_edit(middle, min, max);
        if(edit == calcul)
            return middle;
        else if(edit > calcul)
            return conversion_edit_slider(edit, middle, imax, min, max);
        else
            return conversion_edit_slider(edit, imin, middle, min, max);
    }
}

int nombre_de_chiffre(double x)
{
    int nombre = (int) x;
    int reponse = 0;
    while(nombre != 0)
    {
        nombre /= 10;
        reponse++;
    }
    return reponse;
}

int est_chiffre(char c)
{
    return (c >= '0' && c<='9');
}

void double_to_chaine(double x, char chaine[]) // chaine de taille 7 maximum
{
    int chiffres = nombre_de_chiffre(x);
    int pow_dix = 1;
    int i;
    for(i=1; i<chiffres; i++)
        pow_dix *= 10;
    int entier = (int) x;
    // la gauche
    for(i=0; i<chiffres; i++)
    {
        chaine[i] = '0' + entier/pow_dix;
        entier %= pow_dix;
        pow_dix /= 10;
    }
    if(i<6)
    {
        chaine[i] = '.';
        i++;
    }

    // la droite
    pow_dix = 10;
    for(; i<6; i++)
    {
        chaine[i] = '0' + (((int)(x*pow_dix))%10);
        pow_dix *= 10;
    }
    chaine[6] = 0;
}

double chaine_to_double(char* chaine)
{
    double retour = 0.;
    int etat = 0;
    int i=0;
    double decimale = 0.1;
    while(chaine[i] != 0)
    {
        switch(etat)
        {
            case 0 : //gauche
                if(est_chiffre(chaine[i]))
                {
                    retour *= 10;
                    retour += (double)(chaine[i] - '0');
                }
                else if(chaine[i] == '.' || chaine[i] == ',')
                {
                    etat = 1;
                }
                break;
            default :
                if(est_chiffre(chaine[i]))
                {
                    retour += (double)((chaine[i] - '0')*decimale);
                    decimale *= 0.1;
                }
        }
        i++;
    }

    return retour;
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
        if(!est_chiffre(chaine[i]) && chaine[i]!=',' && chaine[i]!='.')
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

void action_change_edit(HWND hEdit, HWND hSlider, int priorite, double min, double max)
{
    static int nb_fait = 0;

    if(nb_fait == 2)
    {
        nb_fait = 0; //pour le prochain changement
        return;
    }
    nb_fait++;

    if(priorite == 0) // trackbar change
    {
        // On change l'edit
        double nombre = conversion_slider_edit(SendMessage(hSlider, TBM_GETPOS, 0, 0), min, max);
        char chaine[7];
        double_to_chaine(nombre, chaine);
        SendMessage(hEdit, WM_SETTEXT, 1, (LPARAM)chaine);
    }
    else // edit change
    {
        // On change le trackbar
        char chaine [10];
        chaine[0] = sizeof(chaine);
        SendMessage(hEdit, EM_GETLINE, 0, (LPARAM)chaine);
        double valeur = chaine_to_double(chaine);
        int ivaleur = 75; //conversion_edit_slider(valeur, 0, 100, min, max);
        SendMessage(hSlider, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) ivaleur);
    }
}

void action_aide(HWND handle)
{
    MessageBox(handle,"Aide disponible bientôt","Aide",MB_OK);
}
