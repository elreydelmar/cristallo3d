#include "actions.h"

EventStatus* event_status = NULL;

void init_event()
{
    if(event_status == NULL)
    {
        event_status = (EventStatus*) malloc(sizeof(EventStatus));
        event_status->choix_camera = 0;
        event_status->anaglyphe = 0;
        event_status->retro = 0;
        event_status->dist_retro = 12;
        event_status->distance = 12;

        event_status->maille = NULL;
        event_status->nb_x = 1;
        event_status->nb_y = 1;
        event_status->nb_z = 1;
        event_status->espace_atome = 0.5;

        event_status->camera_active = 0;
        event_status->controle = 0;
    }
}

void end_event()
{
    if(event_status != NULL)
    {
        free(event_status);
        event_status = NULL;
    }
}

void action_change_camera(int type)
{
    event_status->choix_camera  = type;
    if(type) // Trackball
        tourner_droite(camera_courante, 0);
}

void action_change_anaglyphe(int checked)
{
    event_status->anaglyphe = checked;
}

void action_activer_retro(int active)
{
    event_status->retro = active;
}

double conversion_slider_edit(int slider, double min, double max)
{
    double x = ((double)slider)/100.;
    return ((max - min)*x*x+min);
}

int conversion_edit_slider(double edit, int imin, int imax, double min, double max)
{
    if(imax - imin < 2)
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
    *((WORD*) chaine) = 10;
    if(SendMessage(handle, EM_GETLINE, 1, (LPARAM)chaine) == 0)
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

void action_change_edit(HWND hEdit, HWND hSlider, int priorite, double min, double max, double* achanger)
{
    static int nb_fait = 0;

    nb_fait++;

    if(priorite == 0) // trackbar change
    {
        if(nb_fait != 2)
        {
            // On change l'edit
            *achanger = conversion_slider_edit(SendMessage(hSlider, TBM_GETPOS, 0, 0), min, max);
            char chaine[7];
            double_to_chaine(*achanger, chaine);
            SendMessage(hEdit, WM_SETTEXT, 1, (LPARAM)chaine);
        }
    }
    else // edit change
    {
        if(nb_fait != 2)
        {
            // On change le trackbar
            char chaine [10];
            *((WORD*) chaine) = 10;
            int reussite = SendMessage(hEdit, EM_GETLINE, 0, (LPARAM)chaine);
            if(reussite == 0)
            {
                SendMessage(hSlider, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) 0);
                action_change_edit(hEdit, hSlider, 0, min, max, achanger);
            }
            else
            {
                *achanger = chaine_to_double(chaine);
                int ivaleur = conversion_edit_slider(*achanger, 1, 100, min, max);
                SendMessage(hSlider, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) ivaleur);
                action_change_edit(hEdit, hSlider, 0, min, max, achanger);
            }
        }
    }

    if(nb_fait == 2)
    {
        nb_fait = 0; //pour le prochain changement
    }
}

void action_default_distance(double valeur)
{
    char chaine[7];
    double_to_chaine(valeur, chaine);
    SendMessage(g_fenetre->t_distance, WM_SETTEXT, 1, (LPARAM)chaine);
}

void action_parcourir()
{
    OPENFILENAME ofn;
    CHAR szFile[255]={0};

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = g_fenetre->fenetre;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = 255;
    ofn.lpstrFilter =
               "Fichier CIF\0*.cif\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileName(&ofn)==TRUE)
    {
        SendMessage(g_fenetre->adresse, WM_SETTEXT, 0, (LPARAM)szFile);
    }
}

void action_generer()
{
    // Charge la maille
    // Charge les donnees de la maille sur la fenetre
    MessageBox(NULL,"G�n�ration de la maille","Maille",MB_OK); // TODO
}

void action_change_nb_x()
{
    if(event_status == NULL)
        return;
    char chaine [10];
    *((WORD*) chaine) = 10;
    int reussite = SendMessage(g_fenetre->nb_x, EM_GETLINE, 0, (LPARAM)chaine);
    if(reussite == 0)
        event_status->nb_x  = 1;
    else
    {
        int nombre = (int)chaine_to_double(chaine);
        event_status->nb_x = (nombre > 0) ? nombre : 1;
    }
}

void action_change_nb_y()
{
    if(event_status == NULL)
        return;
    char chaine [10];
    *((WORD*) chaine) = 10;
    int reussite = SendMessage(g_fenetre->nb_y, EM_GETLINE, 0, (LPARAM)chaine);
    if(reussite == 0)
        event_status->nb_y  = 1;
    else
    {
        int nombre = (int)chaine_to_double(chaine);
        event_status->nb_y = (nombre > 0) ? nombre : 1;
    }
}

void action_change_nb_z()
{
    if(event_status == NULL)
        return;
    char chaine [10];
    *((WORD*) chaine) = 10;
    int reussite = SendMessage(g_fenetre->nb_z, EM_GETLINE, 0, (LPARAM)chaine);
    if(reussite == 0)
        event_status->nb_z  = 1;
    else
    {
        int nombre = (int)chaine_to_double(chaine);
        event_status->nb_z = (nombre > 0) ? nombre : 1;
    }
}

int get_atome_courant()
{
    return SendMessage(g_fenetre->choix_atome, CB_GETCURSEL, 0, 0);
}

void action_change_atome()
{
    // Charge les donnees de l atome
    MessageBox(NULL,"Changement de l atome","Maille",MB_OK);
}

double slider_to_double(int i, double min, double max)
{

    return min + (max - min)*((double)i - 1.)/99.;
}

void action_change_couleur()
{
    if(event_status->maille != NULL)
    {
        int atome = get_atome_courant();
        if(atome != CB_ERR)
        {
            event_status->maille->types[atome].index_couleur = SendMessage(g_fenetre->couleur, CB_GETCURSEL, 0, 0);
        }
    }
}

void action_change_taille()
{
    if(event_status->maille != NULL)
    {
        int atome = get_atome_courant();
        if(atome != CB_ERR)
        {
            double a = event_status->maille->a;
            event_status->maille->types[atome].rayon_ionique = slider_to_double(SendMessage(g_fenetre->s_taille, TBM_GETPOS, 0, 0), a/20., a);
        }
    }
}

void action_change_espace()
{
    if(event_status->maille != NULL)
    {
        double a = event_status->maille->a;
        event_status->espace_atome = slider_to_double(SendMessage(g_fenetre->s_espace_atome, TBM_GETPOS, 0, 0), a/20., a);
    }
}

void action_defaut(HWND handle)
{
    MessageBox(handle,"Mise par defaut","Defaut",MB_OK);
}

void action_aide(HWND handle)
{
    MessageBox(handle,"Aide disponible bient�t","Aide",MB_OK);
}

void action_up()
{
    avancer_camera(camera_courante, 0.1);
    if(event_status->choix_camera)  // Trackball
    {
        tourner_gauche(camera_courante, 0);
    }
}

void action_down()
{
    reculer_camera(camera_courante, 0.1);
    if(event_status->choix_camera)  // Trackball
    {
        tourner_gauche(camera_courante, 0);
    }
}

void action_left()
{
    rotate_anticlockwise(camera_courante, 0.1);
}

void action_right()
{
    rotate_clockwise(camera_courante, 0.1);
}

void action_controle(int valeur)
{
    event_status->controle = valeur;
}

void changer_activation_camera()
{
    event_status->camera_active = !event_status->camera_active;
}

void action_mouse_move(int x, int y)
{
    if(event_status->camera_active)
    {
        if(!event_status->choix_camera) // Freefly
        {
            if(!event_status->controle)
            {
                if(x > 0)
                    tete_gauche(camera_courante, PAS_TETE *(double)x);
                else if(x < 0)
                    tete_droite(camera_courante, -PAS_TETE *(double)x);

                if(y > 0)
                    tete_haut(camera_courante, PAS_TETE *(double)y);
                else if(y < 0)
                    tete_bas(camera_courante, -PAS_TETE *(double)y);
            }
            else
            {
                if(x > 0)
                    glisser_droite(camera_courante, PAS_GLISSER *(double)x);
                else if(x < 0)
                    glisser_gauche(camera_courante, -PAS_GLISSER *(double)x);

                if(y > 0)
                    glisser_haut(camera_courante, PAS_GLISSER *(double)y);
                else if(y < 0)
                    glisser_bas(camera_courante, -PAS_GLISSER *(double)y);
            }
        }
        else    // Trackball
        {
            if(x > 0)
                tourner_droite(camera_courante, 0.1 *(double)x);
            else if(x < 0)
                tourner_gauche(camera_courante, -0.1 *(double)x);

            if(y > 0)
                tourner_haut(camera_courante, 0.1 *(double)y);
            else if(y < 0)
                tourner_bas(camera_courante, -0.1 *(double)y);
        }
    }
}

void action_zoom(int sens)
{
    if(sens) // zoom
        zoom(camera_courante, 1.1);
    else    // dezoom
        zoom(camera_courante, 0.9);
}
