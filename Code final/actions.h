#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "fenetre.h"

/*
    Contient toutes les actions possibles activees par evenement
*/

void action_change_camera(int type); // 1 si trackball, 0 si freefly
void action_change_anaglyphe(int checked); // 1 si checked, 0 sinon
void action_aide(HWND handle);

#endif // ACTIONS_H_INCLUDED
