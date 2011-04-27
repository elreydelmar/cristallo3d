#include <stdio.h>
#include <stdlib.h>
#include "geometrie.h"
#include "camera.h"


void avancer_camera(Camera* c, double pas)
{
    pos.x = pos.x + pas;
    cible.x = cible.x + pas;

}

void reculer_camera(Camera* c, double pas)
{
    avancer_camera(Camera* c, double (-pas));
}


void glisser_gauche(Camera* c, double pas)
{
    pos.y = pos.y + pas;
    cible.y = cible.y + pas;
}

void glisser_droite(Camera* c, double pas)
{
    glisser_gauche(Camera* c, double (-pas));
}

void glisser_haut(Camera* c, double pas)
{

    pos.z = pos.z + pas;
    cible.z = cible.z + pas;
}

void glisser_bas(Camera* c, double pas);

{
    glisser_haut(Camera* c, double (-pas)
}



void zoom(Camera* c, double facteur); // change la "focale"

{
    fovy = facteur*fovy
}



void tourner_gauche(Camera* c, double pas)

{
N=norme(sub_pts(pos,cible) ); /*norme et sub_pts (soustraction) sont dans le geometrie.h*/

pos = pos - pas; /* Le sens de rotation vers la gauche correspond a une translation vers la gauche de 'pas', donc on ajoute - pas quel que soit son signe */

norme (sub_pts(pos,cible) ) = N;

/* il manque un truc pour dire qu'on extrait pos... */

}


void tourner_droite(Camera* c, double pas)
{
    tourner_droite(Camera* c, double (-pas));
}



void tourner_haut(Camera* c, double pas);

void tourner_bas(Camera* c, double pas);


