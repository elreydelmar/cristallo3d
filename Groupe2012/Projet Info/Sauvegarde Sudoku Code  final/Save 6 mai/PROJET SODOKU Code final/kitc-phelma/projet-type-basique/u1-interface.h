// u1-interface.h
// Sentinelle d'inclusion
#ifndef _u1_interface_h
#define _u1_interface_h

// Declarations externes - inclusion des fichiers d'entete
#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>

// Definition des constantes
#define X_ZONE  30      // X de la zone
#define Y_ZONE  30      // Y de la zone
#define L_ZONE  450     // Largeur de la zone
#define H_ZONE  450     // Hauteur de la zone

// Declaration des objets de l'interface
struct Interface
{
    Fl_Double_Window*   Fenetre ;
    DrawingArea*        ZoneDessin ;
    Fl_Button*          BoutonQuitter ;
    Fl_Button*          BoutonChuck ;
    Fl_Button*          BoutonFacile ;
    Fl_Button*          BoutonMoyen ;
    Fl_Button*          BoutonExpert ;
    Fl_Button*          BoutonChercherSolutions;
    //Fl_Check_Button*    Solution ;
    Fl_Button*          BoutonAide ;
    Fl_Button*          BoutonKonami ;
    Fl_Button*          BoutonVador;
    Fl_Value_Output*    ChampNum;
    Fl_Value_Output*    Minutes;
    Fl_Value_Output*    Heures;
    Fl_Value_Output*    Secondes;

    Fl_Value_Input*     ChampSaisieNum;
    Fl_Group*           GroupeBoutonsSolution;
    Fl_Round_Button*    BoutonSolOui;
    Fl_Output*          NotificationErreur;
} ;

// Declaration des objets de l'interface generale - ne pas supprimer
extern struct Interface gInterface ;



 struct Carre
    {
        int Prems;
        int Cases[8];
    };



// Declaration des sous-programmes
void CreerInterface();
void ActualiserInterface();



#endif // _u1_interface_h
