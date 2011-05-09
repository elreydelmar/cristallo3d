#include "camera.h"


Camera* camera_courante = NULL;

void avancer_camera(Camera* c, double pas)
{

}

void reculer_camera(Camera* c, double pas)
{

}

void glisser_gauche(Camera* c, double pas)
{
 c->origine = add_pts(c->origine,mult_scal_pts(-pas, c->y));
}

void glisser_droite(Camera* c, double pas)
{
 c->origine = add_pts(c->origine,mult_scal_pts(pas, c->y));
}

void glisser_haut(Camera* c, double pas)
{
 c->origine = add_pts(c->origine,mult_scal_pts(pas, c->x));
}

void glisser_bas(Camera* c, double pas)
{
 c->origine = add_pts(c->origine,mult_scal_pts(-pas, c->x));
}

void tete_gauche(Camera* c, double pas)
{

}

void tete_droite(Camera* c, double pas)
{

}

void tete_haut(Camera* c, double pas)
{

}

void tete_bas(Camera* c, double pas)
{

}

void zoom(Camera* c, double facteur)
{
 c->changement_zoom = 1;
 c->fovy = c->fovy*facteur;
}

void rotate_clockwise(Camera* c, double pas)
{

}

void rotate_anticlockwise(Camera* c, double pas)
{

}

void tourner_gauche(Camera* c, double pas)
{


}


void tourner_droite(Camera* c, double pas)
{

}

void tourner_haut(Camera* c, double pas)
{

}

void tourner_bas(Camera* c, double pas)
{

}


