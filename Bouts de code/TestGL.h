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


void dessiner_repere(unsigned int echelle);
void dessiner_cube(double arete, Couleur couleur, unsigned int echelle);
void dessiner_cylindre(Cylindre cylindre, Couleur couleur);
void dessiner_sphere(Sphere sphere, Couleur couleur, Point centre);

void set_couleur(Couleur couleur);
void set_point(Point p);

void dessiner_point(Point point, Couleur couleur);
void dessiner_ligne(Ligne ligne, Couleur couleur);

#endif // TESTGL_H_INCLUDED
