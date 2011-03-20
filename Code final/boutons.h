#ifndef BOUTONS_H_INCLUDED
#define BOUTONS_H_INCLUDED

#include <windows.h>
#include <commctrl.h>
#include "const_fenetre.h"
#include "type_fenetre.h"

// Les ID
#define ID_FREEFLY 110
#define ID_TRACKBALL 111
#define ID_ANAGLYPHE 112
#define ID_RETRO 113
#define ID_S_RETRO 114
#define ID_T_RETRO 115
#define ID_S_DISTANCE 116
#define ID_T_DISTANCE 117
#define ID_ORDI 118
#define ID_SALLE 119
#define ID_AMPHI 120
#define ID_ADRESSE 121


void afficher_boutons(Fenetre* fenetre);
void boutons_camera(Fenetre* fenetre);
void boutons_maille(Fenetre* fenetre);
/*


void creer_check_box(LPCTSTR legende, int id, HWND hParent, HINSTANCE instance, Rect pos)
{
    CreateWindow("BUTTON", legende, WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, pos.x, pos.y, pos.w, 16, hParent, (HMENU)id, instance, NULL);
}

void creer_slider(LPCTSTR legende, int id, HWND hParent, HINSTANCE instance, Rect pos, int i_min, int i_max, int v_min, int v_max)
{
    CreateWindow(TRACKBAR_CLASS, legende, WS_CHILD|WS_VISIBLE, pos.x, pos.y, pos.w, pos.h, hParent, (HMENU)id, instance, NULL);
}
*/

#endif // BOUTONS_H_INCLUDED
