#include "actions.h"
#include "boutons.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

EventStatus* event_status = NULL;

void init_event()
{
    if(event_status == NULL)
    {
        event_status = (EventStatus*) malloc(sizeof(EventStatus));
        event_status->choix_camera = 1;
        event_status->anaglyphe = 0;
        event_status->retro = 0;
        event_status->dist_retro = 12;
        event_status->distance = 12;
        event_status->adresse_fichier[0] = 0;
        event_status->nom_fichier[0] = 0;


        event_status->maille = NULL;
        event_status->nb_x = 1;
        event_status->nb_y = 1;
        event_status->nb_z = 1;
        event_status->espace_atome = 0.5;


        event_status->camera_active = 0;
        event_status->controle = 0;
        event_status->camera_auto = 0;
    }
}

void end_event()
{
    if(event_status != NULL)
    {
        free_maille(event_status->maille);
        free(event_status);
        event_status = NULL;
    }
}

void action_change_camera(int type)
{
    event_status->choix_camera  = type;
    if(type && event_status->maille != NULL) // Trackball
        tourner_droite(camera_courante, 0);
}

void action_change_anaglyphe(int checked)
{
    event_status->anaglyphe = checked;

    if(!checked) // On remet tout au propre
    {
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDisable(GL_BLEND);
    }
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
    CHAR szFileTitle[255]={0};

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = g_fenetre->fenetre;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = 255;

    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle= 255;
    ofn.lpstrFilter =
               "Fichier CIF\0*.cif\0";

    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = "mailles";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileName(&ofn)==TRUE)
    {
        strcpy(event_status->adresse_fichier, szFile);
        SendMessage(g_fenetre->adresse, WM_SETTEXT, 0, (LPARAM)szFile);

        strcpy(event_status->nom_fichier, szFileTitle);
        SendMessage(g_fenetre->nom, WM_SETTEXT, 0, (LPARAM)szFileTitle);

    }
}

void action_generer()
{
    // Charge la maille
    // Charge les donnees de la maille dans premaille
    Premaille premaille;
    if(charger_maille(event_status->adresse_fichier, &premaille))
    {
       MessageBox(NULL,"Erreur fichier invalide","Maille",MB_OK);
       supp_premaille(premaille);
       return;
    }
    premaille_to_maille(premaille, &(event_status->maille));

    // On genere l octree
    charger_octree(event_status->maille, event_status->nb_x, event_status->nb_y, event_status->nb_z);
    // BUG A REGLER SI ON REPREND LE PROJET DE GROUPE
    charger_octree(event_status->maille, event_status->nb_x+2, event_status->nb_y+2, event_status->nb_z+2);
    charger_octree(event_status->maille, event_status->nb_x, event_status->nb_y, event_status->nb_z);
    MessageBox(NULL,"Maille générée","Maille",MB_OK); // TODO


    supp_premaille(premaille);

    // On ajoute les atomes dans le menu defilant
    // D'abord on jarte tout
    int retour = 1;
    while(retour != CB_ERR && retour != 0)
    {
        retour = SendMessage(g_fenetre->choix_atome,CB_DELETESTRING,0,0);
    }
    // On ajoute ensuite tout
    int i;
    for(i=0; i<event_status->maille->nb_type_atomes; i++)
    {
        SendMessage(g_fenetre->choix_atome,CB_ADDSTRING,0, (LPARAM)event_status->maille->types[i].symbole);
    }

    int pos_slider = conversion_edit_slider(event_status->maille->agrandissement, 0, 100, 0.01, 10.0);
    SendMessage(g_fenetre->s_espace_atome, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) pos_slider);

    // Verifie que l'on a pas charge deux fois OpenGL
    static int gl_charge = 1;
    if(gl_charge)
    {
        init_gl(g_fenetre);
        InitGL();
        gl_charge = 0;
    }
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
        // On genere l octree
        if(event_status->maille != NULL)
        {
            charger_octree(event_status->maille, event_status->nb_x, event_status->nb_y, event_status->nb_z);
            // BUG A REGLER SI ON REPREND LE PROJET DE GROUPE
            charger_octree(event_status->maille, event_status->nb_x+2, event_status->nb_y+2, event_status->nb_z+2);
            charger_octree(event_status->maille, event_status->nb_x, event_status->nb_y, event_status->nb_z);
        }
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
        // On genere l octree
        if(event_status->maille != NULL)
        {
            charger_octree(event_status->maille, event_status->nb_x, event_status->nb_y, event_status->nb_z);
            // BUG A REGLER SI ON REPREND LE PROJET DE GROUPE
            charger_octree(event_status->maille, event_status->nb_x+2, event_status->nb_y+2, event_status->nb_z+2);
            charger_octree(event_status->maille, event_status->nb_x, event_status->nb_y, event_status->nb_z);
        }
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
        // On genere l octree
        if(event_status->maille != NULL)
        {
            charger_octree(event_status->maille, event_status->nb_x, event_status->nb_y, event_status->nb_z);
            // BUG A REGLER SI ON REPREND LE PROJET DE GROUPE
            charger_octree(event_status->maille, event_status->nb_x+2, event_status->nb_y+2, event_status->nb_z+2);
            charger_octree(event_status->maille, event_status->nb_x, event_status->nb_y, event_status->nb_z);
        }
    }
}

int get_atome_courant()
{
    return SendMessage(g_fenetre->choix_atome, CB_GETCURSEL, 0, 0);
}


void action_change_atome()
{
    // Charge les donnees de l atome
    int atome_selectionne = get_atome_courant();
    if(atome_selectionne == CB_ERR)
        return;
    SendMessage(g_fenetre->couleur, CB_SETCURSEL, event_status->maille->types[atome_selectionne].index_couleur,0);

    int pos_slider = conversion_edit_slider(event_status->maille->types[atome_selectionne].rayon_ionique, 0, 100, 0.01, 1.0);
    SendMessage(g_fenetre->s_taille, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) pos_slider);
}

double slider_to_double(int i, double min, double max)
{

    return min + (max - min)*((double)i)/100.;
}

int double_to_slider(double x, double min, double max)
{
    return ((int)((x-min)*100./(max - min)));
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
            event_status->maille->types[atome].rayon_ionique = conversion_slider_edit(SendMessage(g_fenetre->s_taille, TBM_GETPOS, 0, 0), 0.01, 1.00);
        }
    }
}

void action_change_espace()
{
    if(event_status->maille != NULL)
    {
        event_status->maille->agrandissement = conversion_slider_edit(SendMessage(g_fenetre->s_espace_atome, TBM_GETPOS, 0, 0), 0.01, 10);
        //slider_to_double(SendMessage(g_fenetre->s_espace_atome, TBM_GETPOS, 0, 0), 0.1, 10);
    }
}

void action_defaut(HWND handle)
{
    if(event_status->maille != NULL)
        camera_par_defaut();
    SendMessage(g_fenetre->trackball, BM_CLICK, 0, 0);

}

void action_aide(HWND handle)
{
    HINSTANCE err = ShellExecute(NULL,"open", "aide.pdf",NULL, "extern",SW_SHOWNORMAL);
    if((int)err ==  SE_ERR_NOASSOC)
        MessageBox(NULL, "Erreur : Adobe Reader n'est pas associé avec les fichiers pdf", "Aide",MB_OK);
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

void action_demarrer_camera_auto()
{
    if(event_status->camera_auto)
    {
        event_status->camera_auto = 0;
    }
    else
    {
        event_status->camera_auto = 1;
        SendMessage(g_fenetre->trackball, BM_CLICK, 0, 0);
        SendMessage(g_fenetre->fenetre, CAMERA_AUTO, 0, 0);
    }


}

void action_camera_automatique()
{
    static clock_t derniere_frame = clock() - 2*NB_CLOCKS_ECART_TOUCHE;
    clock_t present = clock();
    if(present - derniere_frame > NB_CLOCKS_ECART_TOUCHE)
    {
        derniere_frame = present;
        tourner_droite(camera_courante, 0.1);

        display();
        drawscene();
        afficher_dessin();
        update_gl();
    }
    if(event_status->camera_auto)
    {
        SendMessage(g_fenetre->fenetre, CAMERA_AUTO, 0, 0);
    }
}

void changer_activation_camera()
{
    if(event_status->maille == NULL)
        event_status->camera_active = 0; // pas besoin de camera, on n'a pas de maille
    else
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
    /*
    if(sens) // zoom
        zoom(camera_courante, 1.1);
    else    // dezoom
        zoom(camera_courante, 0.9);
        */
}

void action_molette(int sens)
{
    sens %= 360;
    sens = (sens < 180);
    int valeur = SendMessage(g_fenetre->s_espace_atome, TBM_GETPOS, 0, 0);
    if(sens)
    {
        valeur += 2;
        if(valeur>100)
            valeur = 100;
    }
    else
    {
        valeur -= 2;
        if(valeur<=0)
            valeur = 0;
    }
    SendMessage(g_fenetre->s_espace_atome, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) valeur);
    event_status->maille->agrandissement = conversion_slider_edit(SendMessage(g_fenetre->s_espace_atome, TBM_GETPOS, 0, 0), 0.01, 10);
}

void drawscene()
{
    if(event_status != NULL)
    {
        if(event_status->maille != NULL)
        {
            afficher_maille(event_status->maille);
        }
        else
        {
            afficher_image();
        }
    }
}

void display()
{

    // matrix + glClear
    if(event_status != NULL)
    {
        nouveau_dessin();
        if(event_status->maille != NULL)
        {
            if(event_status->anaglyphe)
            {
                display_anaglyphe(camera_courante, event_status->retro, event_status->dist_retro, event_status->distance);
            }
            else
            {
                set_camera(g_fenetre->gl_width, g_fenetre->gl_height,0);
            }
        }
    }
}

void action_enregistrer()
{
                int i;
                TCHAR buf[255];
                UINT GetDlgItemText (HWND hDlg,int nIDDlgItem,LPTSTR lpString,int nMaxCount); //initialisation
                UINT freefps;
                freefps=GetDlgItemText(g_fenetre->menu, ID_NOM, buf, 256);



                strcat(buf, ".txt");
                FILE * fichier = fopen(buf,"w");
                if(fichier == NULL) // Test ouverture canal
                {
                    MessageBox(NULL,"Erreur Fichier","Enregistrement",MB_OK);
                }

                freefps=GetDlgItemText(g_fenetre->menu, ID_NB_X, buf, 256);
                fprintf(fichier, "%s\n",buf);
                freefps=GetDlgItemText(g_fenetre->menu, ID_NB_Y, buf, 256);
                fprintf(fichier, "%s\n",buf);
                freefps=GetDlgItemText(g_fenetre->menu, ID_NB_Z, buf, 256);
                fprintf(fichier, "%s\n",buf);
                fprintf(fichier, "%f\n",event_status->maille->agrandissement);

fprintf(fichier, "%d\n",event_status->maille->nb_type_atomes);

                for(i=0; i<event_status->maille->nb_type_atomes; i++)
                {
                fprintf(fichier, "%s\n",event_status->maille->types[i].symbole);
                fprintf(fichier, "%d\n",event_status->maille->types[i].index_couleur);
                fprintf(fichier, "%f\n",event_status->maille->types[i].rayon_ionique);
                }



                fclose(fichier);
                MessageBox(NULL,"Session enregistrée","Enregistrement",MB_OK);


}

void action_generer_personnelle()
{

}

void action_charger()
{
OPENFILENAME ofn;
    CHAR szFile[255]={0};
    CHAR szFileTitle[255]={0};

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = g_fenetre->fenetre;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = 255;

    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle= 255;
    ofn.lpstrFilter =
               "Fichier TXT\0*.txt\0";

    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = "mailles";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileName(&ofn)==TRUE)
    {
        strcpy(event_status->adresse_fichier, szFile);
        SendMessage(g_fenetre->adresse, WM_SETTEXT, 0, (LPARAM)szFile);

        strcpy(event_status->nom_fichier, szFileTitle);
        SendMessage(g_fenetre->nom, WM_SETTEXT, 0, (LPARAM)szFileTitle);

        FILE * fichier = fopen (szFile, "r");

        TCHAR contenu [255];
        //1ere ligne
        fgets (contenu, 255, fichier);
        //printf("x : %s\n", contenu);
        SendMessage(g_fenetre->nb_x, WM_SETTEXT, 0,(LPARAM)contenu);
        action_change_nb_x();
        //seconde
        fgets (contenu, 255, fichier);
        //printf("y : %s\n", contenu);
        SendMessage(g_fenetre->nb_y, WM_SETTEXT, 0,(LPARAM)contenu);
        action_change_nb_y();

        //troisieme...
        fgets (contenu, 255, fichier);
        //printf("z : %s\n", contenu);
        SendMessage(g_fenetre->nb_z, WM_SETTEXT, 0, (LPARAM)contenu);
        action_change_nb_z();

        fgets (contenu, 255, fichier);
        float nbs_espace_atome = atof (contenu);
        //printf("nbs_espace_atome : %f\n", nbs_espace_atome);
        event_status->maille->agrandissement = nbs_espace_atome;

        fgets (contenu, 255, fichier);
        int nbatome = atoi (contenu);
        //printf("nb atome : %s\n", contenu);
        int i;

        for(i=0; i<nbatome; i++)
                {
        fgets (contenu, 255, fichier);
        //printf("atome : %s\n", contenu);

        fgets (contenu, 255, fichier);
        float nbcouleur = atof (contenu);
        //printf ( "nbcouleur = %s\n", contenu);
        event_status->maille->types[i].index_couleur =  nbcouleur;


        fgets (contenu, 255, fichier);
        float nbs_taille = atof(contenu);
        //printf("nbs_taille : %f\n", nbs_taille);
        event_status->maille->types[i].rayon_ionique = nbs_taille;

                }
fclose(fichier);

    } return;
}
