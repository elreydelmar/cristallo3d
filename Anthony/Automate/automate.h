#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED

#include "fichier.h"
#include "lignes.h"

// Automate
// Retour par defaut : 0 si non trouve et non fin de ligne, 1 si trouve et non fin de ligne, 2 si non trouve et fin de ligne, 3 si trouve et fin de ligne le 3eme bit est le fin de fichier
int detection_reel(FILE* fichier, double* reel); // Le curseur est cense etre deja avant le reel. Si le reel n'est pas detecte, la fonction renvoie 0, 1 si le reel est detecte. Le reel est stocke dans *reel.
int detection_mot(FILE* fichier, const char* a_detecter); // Renvoie le retour par defaut
int aller_prochaine_commande(FILE* fichier); // Renvoie le retour par defaut


int charger_maille(char* nom_du_fichier, Maille* maille); // Renvoie 0 si pas d'erreur
int automate(FILE* fichier, Maille* maille);    // renvoie 0 si pas d erreur


void traiter_sous_commande(FILE* fichier, Maille* maille, int* etat, int* retour, char* c, const char* a_detecter, int etat_a_atteindre); // fini
void etat_nouvelle_commande(FILE* fichier, Maille* maille, int* etat, int* retour, char* c);
void etat_cell(FILE* fichier, Maille* maille, int* etat, int* retour, char* c); // fini
void etat_cell_length(FILE* fichier, Maille* maille, int* etat, int* retour, char* c); // fini
void etat_cell_angle(FILE* fichier, Maille* maille, int* etat, int* retour, char* c); // fini
void etat_sym_equiv_pos_as(FILE* fichier, Maille* maille, int* etat, int* retour, char* c); // fini

// Gestion des symmetry
L_ligne* automate_symmetry(FILE* fichier, int* etat, int* retour, char* c); // ajouter la gestion des signes

// Lecture des atomes

// Tests
char is_chiffre(char c);
char is_operateur(char c);
char is_variable(char c);

// Converting
Op char_to_op(char c);
double char_to_chiffre(char c);


void afficher_arbre(Arbre* a);
void afficher_l_ligne(L_ligne* l);

#endif // AUTOMATE_H_INCLUDED
