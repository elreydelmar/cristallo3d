#include "fichier.h"

FILE* ouvrir_fichier(char* nom_du_fichier)
{
    return fopen(nom_du_fichier, "r");
}

char lire_lettre(FILE* fichier)
{
     char c = fgetc(fichier);
     return c;
}

void fermeture_fichier(FILE* nom_du_fichier)
{
    fclose(nom_du_fichier);
}
