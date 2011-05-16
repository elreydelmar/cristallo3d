#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "type_ligne.h"
#include "err_fichier.h"
#include "premaille.h"

#define LONGUEUR_LIGNE_MAX 250

int charger_maille(char* nom_du_fichier); // l'entier renvoye est l erreur ou non de la fonction

void init_premaille(Premaille* premaille);
void supp_premaille(Premaille premaille);

// Les types
int type_de_ligne(char* ligne);
int type_de_ligne_cell(char* ligne);
int type_de_ligne_cell_angle(char* ligne);
int type_de_ligne_cell_length(char* ligne);
int type_de_ligne_atome(char* ligne);

// Les actions
void act_uniligne(char* ligne, int type, Premaille* premaille);
void act_donnees(char* ligne, L_int* types, Premaille* premaille);
void act_symmetry(char* ligne, Premaille* premaille);
void act_atome(char* label, double x, double y, double z, Premaille* premaille);

// Automates
// Tests
char is_chiffre(char c);
char is_operateur(char c);
char is_variable(char c);

// Converting
Op char_to_op(char c);
double char_to_chiffre(char c);

// Test
void afficher_arbre(Arbre* a);
void afficher_l_ligne(L_ligne* l);

#endif // FICHIER_H_INCLUDED
