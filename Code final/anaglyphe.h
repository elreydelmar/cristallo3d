#ifndef ANAGLYPHE_H_INCLUDED
#define ANAGLYPHE_H_INCLUDED

#include "GLbasic.h"
#include "camera.h"
#include "fenetre.h"

extern void drawscene();
void display_anaglyphe(Camera* camera, int retro, double distance_retro, double distance_ecran);

#endif // ANAGLYPHE_H_INCLUDED
