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
#define ID_PARCOURIR 122
#define ID_GENERER 123

#define ID_NB_X 124
#define ID_NB_Y 125
#define ID_NB_Z 126

#define ID_ATOME  132
#define ID_COULEUR 133

#define ID_S_TAILLE 127
#define ID_S_ESPACE 128

#define ID_DEFAULT 130
#define ID_HELP 131


void afficher_boutons(Fenetre* fenetre);
    void boutons_camera(Fenetre* fenetre);
    void boutons_maille(Fenetre* fenetre);
    void autres_boutons(Fenetre* fenetre);

#endif // BOUTONS_H_INCLUDED
