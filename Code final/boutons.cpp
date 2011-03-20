#include "boutons.h"

void afficher_boutons(Fenetre* fenetre)
{
    InitCommonControls(); // loads common control's DLL

    boutons_camera(fenetre);
    boutons_maille(fenetre);
}

void boutons_camera(Fenetre* fenetre)
{
    // Le cadre
    fenetre->cam = CreateWindow("BUTTON", "Camera", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, ALINEA_MENU,Y_CAMERA, WIDTH_MENU,HEIGHT_CAMERA, fenetre->menu, NULL, fenetre->instance, NULL);

    // Trackball ou Freefly
    fenetre->freefly = CreateWindow("BUTTON", "Freefly", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP, ALINEA_BLOC, 20, 140, Y_CHAR, fenetre->cam, (HMENU)ID_FREEFLY, fenetre->instance, NULL);
    fenetre->trackball = CreateWindow("BUTTON", "Trackball", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, ALINEA_BLOC+140, 20, 80, Y_CHAR, fenetre->cam, (HMENU)ID_TRACKBALL, fenetre->instance, NULL);
    SendMessage(fenetre->freefly, BM_SETCHECK, BST_CHECKED, 0);

    // Anaglyphe ou non
    fenetre->anaglyphe = CreateWindow("BUTTON", "Anaglyphe", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, ALINEA_BLOC, 25+Y_CHAR, 100, Y_CHAR, fenetre->cam, (HMENU)ID_ANAGLYPHE, fenetre->instance, NULL);

    // Retroprojecteur
    fenetre->c_retro = CreateWindow("BUTTON", "Retroprojecteur", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, ALINEA_BLOC/2, 35+2*Y_CHAR, WIDTH_MENU-ALINEA_BLOC, HEIGHT_RETRO, fenetre->cam, (HMENU)ID_RETRO, fenetre->instance, NULL);
    fenetre->retro =  CreateWindow("BUTTON", "Activer", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, ALINEA_BLOC/2, 2*Y_CHAR, 150, Y_CHAR, fenetre->c_retro, (HMENU)ID_RETRO, fenetre->instance, NULL);
    // Slider
    fenetre->s_retro = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE, ALINEA_BLOC/2, 3*Y_CHAR, 170, 3*Y_CHAR, fenetre->c_retro, (HMENU)ID_S_RETRO, fenetre->instance, NULL);
        SendMessage(fenetre->s_retro, TBM_SETRANGE,(WPARAM) TRUE,(LPARAM) MAKELONG(1, 100));  // min. & max. positions
        SendMessage(fenetre->s_retro, TBM_SETPAGESIZE, 0, (LPARAM) 4);
        SendMessage(fenetre->s_retro, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) 50);   // La position initiale du slider
    // Box
    fenetre->t_retro = CreateWindow("EDIT", "5", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, ALINEA_BLOC/2 + 175, 3*Y_CHAR + 2, 50, Y_CHAR, fenetre->c_retro, (HMENU)ID_T_RETRO, fenetre->instance, NULL);


    // Distance ecran
    fenetre->c_distance = CreateWindow("BUTTON", "Distance avec l'écran", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, ALINEA_BLOC/2, 35+ 2.5*Y_CHAR + HEIGHT_RETRO, WIDTH_MENU-ALINEA_BLOC, HEIGHT_DIST, fenetre->cam, (HMENU)ID_RETRO, fenetre->instance, NULL);
    // Slider
    fenetre->s_distance = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE, ALINEA_BLOC/2, 2*Y_CHAR, 170, 2*Y_CHAR, fenetre->c_distance, (HMENU)ID_S_DISTANCE, fenetre->instance, NULL);
        SendMessage(fenetre->s_distance, TBM_SETRANGE,(WPARAM) TRUE,(LPARAM) MAKELONG(1, 100));  // min. & max. positions
        SendMessage(fenetre->s_distance, TBM_SETPAGESIZE, 0, (LPARAM) 4);
        SendMessage(fenetre->s_distance, TBM_SETPOS, (WPARAM) TRUE,(LPARAM) 50);   // La position initiale du slider
    // Box
    fenetre->t_distance = CreateWindow("EDIT", "6", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, ALINEA_BLOC/2 + 175, 2*Y_CHAR + 2, 50, Y_CHAR, fenetre->c_distance, (HMENU)ID_T_DISTANCE, fenetre->instance, NULL);
    // Les trois boutons
    fenetre->ordi = CreateWindow("BUTTON", "Ordinateur", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, ALINEA_BLOC/2, 70, 80,2*Y_CHAR, fenetre->c_distance, (HMENU)ID_ORDI, fenetre->instance, NULL);
    fenetre->salle = CreateWindow("BUTTON", "Salle", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, ALINEA_BLOC + 80, 70, 60,2*Y_CHAR, fenetre->c_distance, (HMENU)ID_SALLE, fenetre->instance, NULL);
    fenetre->amphi = CreateWindow("BUTTON", "Amphi", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 3*ALINEA_BLOC/2 + 140, 70, 60,2*Y_CHAR, fenetre->c_distance, (HMENU)ID_AMPHI, fenetre->instance, NULL);


}

void boutons_maille(Fenetre* fenetre)
{
    // Le cadre
    fenetre->maille = CreateWindow("BUTTON", "Maille", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, ALINEA_MENU,Y_MAILLE, WIDTH_MENU,HEIGHT_MAILLE, fenetre->menu, NULL, fenetre->instance, NULL);
    fenetre->adresse = CreateWindow("EDIT", "C:\\", WS_CHILD | WS_VISIBLE | ES_LEFT, ALINEA_BLOC, 3*Y_CHAR + 2, 120, Y_CHAR, fenetre->maille, (HMENU)ID_ADRESSE, fenetre->instance, NULL);
}
