#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

FILE* ouvrir_fichier(char* nom_du_fichier); // ouvre le fichier dont l'adresse est nom_du_fichier

void fermeture_fichier(FILE* fichier); // ferme le fichier

unsigned char lire_lettre(FILE* fichier); // fonction qui renvoie la prochaine lettre et passe a la suivante (le passage a la lettre suivante se fait automatiquement)

int detection_reel(FILE* fichier, double* reel); // Le curseur est cense etre deja avant le reel. Si le reel n'est pas detecte, la fonction renvoie 0, 1 si le reel est detecte. Le reel est stocke dans *reel.


#endif // FICHIER_H_INCLUDED
