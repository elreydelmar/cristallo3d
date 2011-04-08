#ifndef TESTGL_H_INCLUDED
#define TESTGL_H_INCLUDED

struct Couleur
{
    unsigned char r;
    unsigned char v;
    unsigned char b;
};

void dessiner_repere(unsigned int echelle = 1);

void dessiner_cube(double arete, Couleur couleur);

/*
void set_couleur(Couleur couleur);
void set_point(Point p);

void dessiner_point(Point point, Couleur couleur);
//void dessiner_ligne/*adapter*///(Ligne ligne/*adapter*/, Couleur couleur);

#endif // TESTGL_H_INCLUDED
