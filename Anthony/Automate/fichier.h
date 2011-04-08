#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "maille.h"
#include "etats.h"

// Les defines
#define ERR_OUVERTURE_FICHIER 1

// Traitement de la maille
//void init_maille(Maille* maille);

// Traitement de base du fichier DONE
FILE* ouvrir_fichier(char* nom_du_fichier); // ouvre le fichier dont l'adresse est nom_du_fichier
void fermeture_fichier(FILE* fichier); // ferme le fichier
char lire_lettre(FILE* fichier); // fonction qui renvoie la prochaine lettre et passe a la suivante (le passage a la lettre suivante se fait automatiquement)


#endif // FICHIER_H_INCLUDED
