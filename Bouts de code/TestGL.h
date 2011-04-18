#ifndef TESTGL_H_INCLUDED
#define TESTGL_H_INCLUDED
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "geometrie.h"


typedef struct Couleur Couleur;
struct Couleur
{
    unsigned char r;
    unsigned char v;
    unsigned char b;
};

void InitGL();
void init_camera_de_merde();
void update_camera_de_merde();

void nouveau_dessin();
void changerepere(Point O, Point Z); //place le repère au point O, orienté suivant Z
void dessiner_repere(unsigned int echelle);
void dessiner_cube(double arete, Couleur couleur, unsigned int echelle);
void dessiner_cylindre(Cylindre cylindre, Couleur couleur);
void dessiner_sphere(Sphere sphere, Couleur couleur, Point centre);

void set_couleur(Couleur couleur);
void set_point(Point p);

void dessiner_point(Point point, Couleur couleur);
void dessiner_ligne(Couleur couleur, Ligne ligne, double rayon);

#endif // TESTGL_H_INCLUDED
