#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "fenetre.h"

/*
    Contient toutes les actions possibles activees par evenement
*/

// actions par la camera
void action_change_camera(int type); // 1 si trackball, 0 si freefly
void action_change_anaglyphe(int checked); // 1 si checked, 0 sinon

void action_activer_retro(int active); // 1 si activer, 0 sinon
double conversion_slider_edit(int slider, double min, double max);
int conversion_edit_slider(double edit, int imin, int imax, double min, double max);
void double_to_chaine(double x, char chaine[]);
int nombre_de_chiffre(double x);
int est_chiffre(char c);
double chaine_to_double(char* chaine);

void action_update_edit(HWND handle);
void action_change_edit(HWND hEdit, HWND hSlider, int priorite, double min, double max); // 0 si le changement vient de la trackbar
void action_default_distance(double valeur);

// actions par la maille
void action_parcourir();
void action_generer();

void action_change_nb_x();
void action_change_nb_y();
void action_change_nb_z();

void action_aide(HWND handle);


#endif // ACTIONS_H_INCLUDED
