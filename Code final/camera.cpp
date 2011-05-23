#include "camera.h"


Camera* camera_courante = NULL;

void avancer_camera(Camera* c, double pas)
{
    c->origine=add_pts(c->origine, mult_scal_pts(pas,c->z));
}

void reculer_camera(Camera* c, double pas)
{
    c->origine=sub_pts(c->origine, mult_scal_pts(pas,(*c).z));
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
    Point dy, dz;
    dy = mult_scal_pts (-pas, c->y);
    dz = mult_scal_pts (pas, c->z);
    c->z = add_pts(c->z, dy);
    c->y = add_pts(c->y, dz);
    normer (&(c->z));
    normer (&(c->y));
}

void tete_droite(Camera* c, double pas)
{
    Point dy, dz;
    dy = mult_scal_pts (pas, c->y);
    dz = mult_scal_pts (-pas, c->z);
    c->z = add_pts(c->z, dy);
    c->y = add_pts(c->y, dz);
    normer (&(c->z));
    normer (&(c->y));
}

void tete_haut(Camera* c, double pas)
{
    Point dx, dz;
    dx = mult_scal_pts (pas, c->x);
    dz = mult_scal_pts (-pas, c->z);
    c->z = add_pts(c->z, dx);
    c->x = add_pts(c->x, dz);
    normer (&(c->x));
    normer (&(c->z));
}

void tete_bas(Camera* c, double pas)
{
    Point dx, dz;
    dx = mult_scal_pts (-pas, c->x);
    dz = mult_scal_pts (pas, c->z);
    c->z = add_pts(c->z, dx);
    c->x = add_pts(c->x, dz);
    normer (&(c->x));
    normer (&(c->z));
}

void zoom(Camera* c, double facteur)
{
    c->changement_zoom = 1;
    c->fovy = c->fovy*facteur;
    if(c->fovy > FOVY_MAX)
        c->fovy = FOVY_MAX;
    if(c->fovy < FOVY_MIN)
        c->fovy = FOVY_MIN;
}

void rotate_clockwise(Camera* c, double pas)
{
    Point dx, dy;
    dx = mult_scal_pts (-pas, c->x);
    dy = mult_scal_pts (pas, c->y);
    c->x = add_pts(c->x, dy);
    c->y = add_pts(c->y, dx);
    normer (&(c->x));
    normer (&(c->y));
}

void rotate_anticlockwise(Camera* c, double pas)
{
    Point dx, dy;
    dx = mult_scal_pts (pas, c->x);
    dy = mult_scal_pts (-pas, c->y);
    c->x = add_pts(c->x, dy);
    c->y = add_pts(c->y, dx);
    normer (&(c->x));
    normer (&(c->y));
}

void tourner_gauche(Camera* c, double pas)
{
    Point dy;
    Point v;
    double n = norme (sub_pts(c->centre, c->origine));
    dy = mult_scal_pts (-pas, c->y);
    c->origine = sub_pts (c->origine, dy);
    v = sub_pts (c->centre, c->origine);
    v = mult_scal_pts ((n/norme(v)), v);
    c->origine = sub_pts (c->centre, v);
    c->z = v;
    normer (&(c->z));
    c->y = prod_vect(c->z, c->x);
}


void tourner_droite(Camera* c, double pas)
{
    Point dy;
    Point v;
    double n = norme (sub_pts(c->centre, c->origine));
    dy = mult_scal_pts (pas, c->y);
    c->origine = sub_pts (c->origine, dy);
    v = sub_pts (c->centre, c->origine);
    v = mult_scal_pts ((n/norme(v)), v);
    c->origine = sub_pts (c->centre, v);
    c->z = v;
    normer (&(c->z));
    c->y = prod_vect(c->z, c->x);
}

void tourner_haut(Camera* c, double pas)
{
    Point dx;
    Point v;
    double n = norme (sub_pts(c->centre, c->origine));
    dx = mult_scal_pts (pas, c->x);
    c->origine = sub_pts (c->origine, dx);
    v = sub_pts (c->centre, c->origine);
    v = mult_scal_pts ((n/norme(v)), v);
    c->origine = sub_pts (c->centre, v);
    c->z = v;
    normer (&(c->z));
    c->y = prod_vect(c->z, c->x);
}

void tourner_bas(Camera* c, double pas)
{
    Point dx;
    Point v;
    double n = norme (sub_pts(c->centre, c->origine));
    dx = mult_scal_pts (-pas, c->x);
    c->origine = sub_pts (c->origine, dx);
    v = sub_pts (c->centre, c->origine);
    v = mult_scal_pts ((n/norme(v)), v);
    c->origine = sub_pts (c->centre, v);
    c->z = v;
    normer (&(c->z));
    c->y = prod_vect(c->z, c->x);
}


void init_camera()
{
    camera_courante = (Camera*) malloc(sizeof(Camera));
    camera_par_defaut();
}

void camera_par_defaut()
{
    camera_courante->origine.x=1.5;
    camera_courante->origine.y=2;
    camera_courante->origine.z=1;

    camera_courante->x.x= -1.5;
    camera_courante->x.y= -2;
    camera_courante->x.z= 6.25;

    camera_courante->y.x= (2);
    camera_courante->y.y= -1.5;
    camera_courante->y.z=0;

    camera_courante->z.x= (-1.5);
    camera_courante->z.y = (-2);
    camera_courante->z.z= (-1);

    normer(&(camera_courante->x));
    normer(&(camera_courante->y));
    normer(&(camera_courante->z));

    camera_courante->centre.x=0;
    camera_courante->centre.y=0;
    camera_courante->centre.z=0;

    camera_courante->changement_zoom=1;

    camera_courante->fovy=70;
}

void close_camera()
{
    free(camera_courante);
}

double distance_projection(double distance_retro, double distance_ecran)
{
    return (5*distance_ecran - distance_retro);
}
