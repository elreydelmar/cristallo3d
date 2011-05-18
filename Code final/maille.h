#ifndef MAILLE_H_INCLUDED
#define MAILLE_H_INCLUDED

#include "geometrie.h"
#include "octree.h"
#include "GLbasic.h"
#include "premaille.h"
#include "arbre.h"


/*
    Les paramètres de la fonction afficher_maille :
    Maille maille, int nb_x (nombre de fois qu on représente la maile selon x), int nb_y, int nb_z, double espace // entre atomes

*/

const Couleur couleurs[13] =
{
    {150,190,250}, // Bleu clair
    {50,50,200},   // Bleu foncé
    {100,250,140}, // Vert clair
    {20,150,50},   // Vert foncé
    {200,200,20},  // Jaune
    {250,150,20},  // Orange
    {250,150,150}, // Rose
    {250, 50, 50}, // Rouge
    {180, 50, 220}, // Violet
    {150, 100, 50}, // Marron
    {220,220,220}, // Blanc
    {120,120,120}, // Gris
    {20,20,20} // Noir
};

struct _L_Symbole
{
    char symbole[6];
    struct _L_Symbole* suivant;
};
typedef struct _L_Symbole L_Symbole;

typedef struct Maille Maille;
struct Maille
{
    int nb_type_atomes;
    Atome_Type* types;
    Octree* atomes;

// Pour reconstruire les mailles
    L_ligne* lignes;
    L_Pre_Atome* p_atomes;

    double alpha;
    double beta;
    double gamma;
    double a;
    double b;
    double c;
    double agrandissement;

    Couleur couleur_trait;
};

Maille* alloc_maille();
void free_maille(Maille* maille);

int premaille_to_maille(Premaille premaille, Maille** maille);
void charger_octree(Maille* maille, int nx, int ny, int nz);

void label_to_symbole(const char label[10], char symbole[6]);
int ajouter_symbole(L_Symbole** l, const char symbole[6]); // 1 si ajout, 0 sinon
void vider_symbole(L_Symbole* l);
int est_dans_cube(Atome a, double min_x, double min_y, double min_z, double max_x, double max_y, double max_z);
void min_max_from_n(int n, double* min, double* max);
void remplir_maille(Maille m, int nx, int ny, int nz);
//int ajout_octree

int find_type(Atome_Type types[], char label[10], int nb_types);

#endif // MAILLE_H_INCLUDED
