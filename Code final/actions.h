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

void action_update_edit(HWND handle);
void action_change_edit(HWND hEdit, HWND hSlider, int priorite); // 0 si le changement vient du slider

void action_aide(HWND handle);


#endif // ACTIONS_H_INCLUDED
