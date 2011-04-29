#include "boutons.h"

void afficher_boutons(Fenetre* fenetre)
{
    InitCommonControls(); // loads common control's DLL

    boutons_camera(fenetre);
    boutons_maille(fenetre);
    autres_boutons(fenetre);
}

void boutons_camera(Fenetre* fenetre)
{
    // Le cadre
    fenetre->cam = CreateWindow("BUTTON", "Camera", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, ALINEA_MENU,Y_CAMERA, WIDTH_MENU,HEIGHT_CAMERA, fenetre->menu, NULL, fenetre->instance, NULL);

    // Trackball ou Freefly
    fenetre->freefly = CreateWindow("BUTTON", "Freefly", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP, ALINEA_MENU + ALINEA_BLOC, Y_CAMERA + 20, 140, Y_CHAR, fenetre->menu, (HMENU)ID_FREEFLY, fenetre->instance, NULL);
    fenetre->trackball = CreateWindow("BUTTON", "Trackball", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, ALINEA_MENU + ALINEA_BLOC+140, Y_CAMERA + 20, 80, Y_CHAR, fenetre->menu, (HMENU)ID_TRACKBALL, fenetre->instance, NULL);
    SendMessage(fenetre->freefly, BM_SETCHECK, BST_CHECKED, 0);

    // Anaglyphe ou non
    fenetre->anaglyphe = CreateWindow("BUTTON", "Anaglyphe", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, ALINEA_MENU + ALINEA_BLOC, Y_CAMERA + 25+Y_CHAR, 100, Y_CHAR, fenetre->menu, (HMENU)ID_ANAGLYPHE, fenetre->instance, NULL);

    // Retroprojecteur
    fenetre->c_retro = CreateWindow("BUTTON", "Retroprojecteur", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, ALINEA_MENU +ALINEA_BLOC/2, Y_CAMERA+35+2*Y_CHAR, WIDTH_MENU-ALINEA_BLOC, HEIGHT_RETRO, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->retro =  CreateWindow("BUTTON", "Activer", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, ALINEA_MENU +ALINEA_BLOC/2 +ALINEA_BLOC/2,Y_CAMERA+35+2*Y_CHAR + 2*Y_CHAR, 150, Y_CHAR, fenetre->menu, (HMENU)ID_RETRO, fenetre->instance, NULL);
    // Slider
    fenetre->s_retro = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE,ALINEA_MENU +ALINEA_BLOC/2 + ALINEA_BLOC/2,Y_CAMERA+35+2*Y_CHAR + 3*Y_CHAR, 170, 3*Y_CHAR, fenetre->menu, (HMENU)ID_S_RETRO, fenetre->instance, NULL);
        SendMessage(fenetre->s_retro, TBM_SETRANGE,(WPARAM) TRUE,(LPARAM) MAKELONG(1, 100));  // min. & max. positions
        SendMessage(fenetre->s_retro, TBM_SETPAGESIZE, 0, (LPARAM) 4);
    // Box
    fenetre->t_retro = CreateWindow("EDIT", "12", WS_CHILD | WS_VISIBLE, ALINEA_MENU+ALINEA_BLOC/2 + ALINEA_BLOC/2 + 175,Y_CAMERA+35+2*Y_CHAR + 3*Y_CHAR + 2, 50, Y_CHAR, fenetre->menu, (HMENU)ID_T_RETRO, fenetre->instance, NULL);
    SendMessage(fenetre->s_retro, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) 50);   // La position initiale du slider

    // Distance ecran
    fenetre->c_distance = CreateWindow("BUTTON", "Distance avec l'écran", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, ALINEA_MENU +ALINEA_BLOC/2, Y_CAMERA + 35+2.5*Y_CHAR+HEIGHT_RETRO, WIDTH_MENU-ALINEA_BLOC, HEIGHT_DIST, fenetre->menu, NULL, fenetre->instance, NULL);
    // Slider
    fenetre->s_distance = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE, ALINEA_MENU+ALINEA_BLOC/2 + ALINEA_BLOC/2, Y_CAMERA+35+2.5*Y_CHAR+HEIGHT_RETRO + 2*Y_CHAR, 170, 2*Y_CHAR, fenetre->menu, (HMENU)ID_S_DISTANCE, fenetre->instance, NULL);
        SendMessage(fenetre->s_distance, TBM_SETRANGE,(WPARAM) TRUE,(LPARAM) MAKELONG(1, 100));  // min. & max. positions
        SendMessage(fenetre->s_distance, TBM_SETPAGESIZE, 0, (LPARAM) 4);
    // Box
    fenetre->t_distance = CreateWindow("EDIT", "12", WS_CHILD | WS_VISIBLE | ES_NUMBER,ALINEA_MENU+ALINEA_BLOC/2 + ALINEA_BLOC/2+175, Y_CAMERA+35+2.5*Y_CHAR+HEIGHT_RETRO + 2*Y_CHAR + 2, 50, Y_CHAR, fenetre->menu, (HMENU)ID_T_DISTANCE, fenetre->instance, NULL);
        SendMessage(fenetre->s_distance, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) 50);   // La position initiale du slider

    // Les trois boutons
    fenetre->ordi = CreateWindow("BUTTON", "Ordinateur", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,ALINEA_MENU+ALINEA_BLOC/2 + ALINEA_BLOC/2, Y_CAMERA+35+2.5*Y_CHAR+HEIGHT_RETRO + 70, 80,2*Y_CHAR, fenetre->menu, (HMENU)ID_ORDI, fenetre->instance, NULL);
    fenetre->salle = CreateWindow("BUTTON", "Salle", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, ALINEA_MENU+ALINEA_BLOC/2 + ALINEA_BLOC + 80, Y_CAMERA+35+2.5*Y_CHAR+HEIGHT_RETRO + 70, 60,2*Y_CHAR, fenetre->menu, (HMENU)ID_SALLE, fenetre->instance, NULL);
    fenetre->amphi = CreateWindow("BUTTON", "Amphi", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, ALINEA_MENU+ALINEA_BLOC/2 + 3*ALINEA_BLOC/2 + 140, Y_CAMERA+35+2.5*Y_CHAR+HEIGHT_RETRO + 70, 60,2*Y_CHAR, fenetre->menu, (HMENU)ID_AMPHI, fenetre->instance, NULL);
}

void boutons_maille(Fenetre* fenetre)
{
    // Le cadre
    fenetre->maille = CreateWindow("BUTTON", "Maille", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, ALINEA_MENU,Y_MAILLE, WIDTH_MENU,HEIGHT_MAILLE, fenetre->menu, NULL, fenetre->instance, NULL);

    // Entree du fichier
    fenetre->adresse = CreateWindow("EDIT", "C:\\", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, ALINEA_MENU + ALINEA_BLOC/2,Y_MAILLE + 2*Y_CHAR + 2, 120, Y_CHAR, fenetre->menu, (HMENU)ID_ADRESSE, fenetre->instance, NULL);
    fenetre->parcourir = CreateWindow("BUTTON", "Parcourir", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,ALINEA_MENU + ALINEA_BLOC + 120,Y_MAILLE +  3*Y_CHAR/2 + 2, 70,2*Y_CHAR, fenetre->menu, (HMENU)ID_PARCOURIR, fenetre->instance, NULL);
    fenetre->generer_maille = CreateWindow("BUTTON", "Ok", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,ALINEA_MENU + 3*ALINEA_BLOC/2 + 190,Y_MAILLE +  3*Y_CHAR/2 + 2, 30,2*Y_CHAR, fenetre->menu, (HMENU)ID_GENERER, fenetre->instance, NULL);

    // Nombre de mailles a afficher
    CreateWindow("STATIC", "Nombre de mailles à afficher :", WS_CHILD | WS_VISIBLE,ALINEA_MENU + ALINEA_BLOC,Y_MAILLE + 60, WIDTH_MENU-2*ALINEA_BLOC, Y_CHAR, fenetre->menu, NULL, fenetre->instance, NULL);

    CreateWindow("STATIC", "en x :", WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2,Y_MAILLE +  2*Y_CHAR + 50, 45, Y_CHAR, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->nb_x = CreateWindow("EDIT", "1", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,ALINEA_MENU +  ALINEA_BLOC/2+45,Y_MAILLE +  2*Y_CHAR + 50, 20, Y_CHAR, fenetre->menu, (HMENU)ID_NB_X, fenetre->instance, NULL);
    CreateWindow("STATIC", "en y :", WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2+ 75,Y_MAILLE +   2*Y_CHAR + 50, 45, Y_CHAR, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->nb_y = CreateWindow("EDIT", "1", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,ALINEA_MENU +  ALINEA_BLOC/2+45+75,Y_MAILLE +  2*Y_CHAR + 50, 20, Y_CHAR, fenetre->menu, (HMENU)ID_NB_Y, fenetre->instance, NULL);
    CreateWindow("STATIC", "en z :", WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2+ 150,Y_MAILLE +   2*Y_CHAR + 50, 45, Y_CHAR, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->nb_z = CreateWindow("EDIT", "1", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,ALINEA_MENU +  ALINEA_BLOC/2+45+150,Y_MAILLE +  2*Y_CHAR + 50, 20, Y_CHAR, fenetre->menu, (HMENU)ID_NB_Z, fenetre->instance, NULL);

    CreateWindow("STATIC", "Atome :", WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2+30,Y_MAILLE +   11*Y_CHAR/2 + 25, 130, Y_CHAR, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->choix_atome = CreateWindow("COMBOBOX", "Atomes...", WS_CHILD | WS_VISIBLE | CBS_SORT | CBS_DROPDOWNLIST,ALINEA_MENU +  ALINEA_BLOC/2 + 100,Y_MAILLE +   11*Y_CHAR/2 + 20, 130, 20*Y_CHAR, fenetre->menu, (HMENU)ID_ATOME, fenetre->instance, NULL);
    CreateWindow("STATIC", "Couleur :", WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2 + 10,Y_MAILLE +   11*Y_CHAR/2 + 55, 130, Y_CHAR, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->couleur = CreateWindow("COMBOBOX", "Couleur...", WS_CHILD | WS_VISIBLE |CBS_DROPDOWNLIST,ALINEA_MENU +  ALINEA_BLOC/2 + 100,Y_MAILLE +   11*Y_CHAR/2 + 50, 130, 20*Y_CHAR, fenetre->menu, (HMENU)ID_COULEUR, fenetre->instance, NULL);
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Bleu clair");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Bleu foncé");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Vert clair");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Vert foncé");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Jaune");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Orange");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Rose");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Rouge");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Violet");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Marron");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Blanc");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Gris");
        SendMessage(fenetre->couleur, CB_ADDSTRING, 0, (LONG) "Noir");

    CreateWindow("STATIC", "Taille des atomes :", WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2,Y_MAILLE +  11*Y_CHAR/2 + 90, 130, Y_CHAR, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->s_taille = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2 + 130,Y_MAILLE +  5*Y_CHAR + 90, 115, 2*Y_CHAR, fenetre->menu, (HMENU)ID_S_TAILLE, fenetre->instance, NULL);
        SendMessage(fenetre->s_taille, TBM_SETRANGE,(WPARAM) TRUE,(LPARAM) MAKELONG(1, 100));  // min. & max. positions
        SendMessage(fenetre->s_taille, TBM_SETPAGESIZE, 0, (LPARAM) 4);
        SendMessage(fenetre->s_taille, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) 50);   // La position initiale du slider

    CreateWindow("STATIC", "Espace entre atomes :", WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2,Y_MAILLE +   17*Y_CHAR/2 + 90, 145, Y_CHAR, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->s_espace_atome = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE,ALINEA_MENU +  ALINEA_BLOC/2 + 145,Y_MAILLE +  8*Y_CHAR + 90, 100, 2*Y_CHAR, fenetre->menu, (HMENU)ID_S_ESPACE, fenetre->instance, NULL);
        SendMessage(fenetre->s_espace_atome, TBM_SETRANGE,(WPARAM) TRUE,(LPARAM) MAKELONG(1, 100));  // min. & max. positions
        SendMessage(fenetre->s_espace_atome, TBM_SETPAGESIZE, 0, (LPARAM) 4);
        SendMessage(fenetre->s_espace_atome, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) 50);   // La position initiale du slider
}

void autres_boutons(Fenetre* fenetre)
{
    fenetre->defaut = CreateWindow("BUTTON", "Par défaut", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, (WIDTH_MENU-TAILLE_BOUTON-ECART_BOUTON)/2, Y_OTHER, TAILLE_BOUTON,2*Y_CHAR, fenetre->menu, (HMENU)ID_DEFAULT, fenetre->instance, NULL);
    fenetre->aide = CreateWindow("BUTTON", "Aide", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, (WIDTH_MENU+ECART_BOUTON)/2, Y_OTHER, TAILLE_BOUTON,2*Y_CHAR, fenetre->menu, (HMENU)ID_HELP, fenetre->instance, NULL);
}
