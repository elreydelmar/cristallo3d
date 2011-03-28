#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "maille.h"
#include "etats.h"

// Les defines
#define ERR_OUVERTURE_FICHIER 1


// Traitement de base du fichier DONE
FILE* ouvrir_fichier(char* nom_du_fichier); // ouvre le fichier dont l'adresse est nom_du_fichier
void fermeture_fichier(FILE* fichier); // ferme le fichier
char lire_lettre(FILE* fichier); // fonction qui renvoie la prochaine lettre et passe a la suivante (le passage a la lettre suivante se fait automatiquement)

// Automate
// Retour par defaut : 0 si non trouve et non fin de ligne, 1 si trouve et non fin de ligne, 2 si non trouve et fin de ligne, 3 si trouve et fin de ligne
int detection_reel(FILE* fichier, double* reel); // Le curseur est cense etre deja avant le reel. Si le reel n'est pas detecte, la fonction renvoie 0, 1 si le reel est detecte. Le reel est stocke dans *reel.
int detection_mot(FILE* fichier, char* a_detecter); // Renvoie le retour par defaut
int aller_prochaine_commande(FILE* fichier); // Renvoie le retour par defaut

int charger_maille(char* nom_du_fichier, Maille* maille); // Renvoie 0 si pas d'erreur
int automate(FILE* fichier, Maille* maille);    // renvoie 0 si pas d erreur

#endif // FICHIER_H_INCLUDED
