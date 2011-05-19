#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* ouvrir_fichier(char* nom_du_fichier); // fonction qui ouvre le fichier dont l'adresse est nom_du_fichier
void fermeture_fichier(FILE* fichier); // ferme le fichier
char lire(FILE* fichier); // fonction qui renvoie la prochaine lettre et passe a la suivante (le passage a la lettre suivante se fait automatiquement)

