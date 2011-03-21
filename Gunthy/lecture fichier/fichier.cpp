#include "fichier.h"

FILE* ouvrir_fichier(char* nom_du_fichier)
{
    return fopen(nom_du_fichier, "r");
}

char lire_lettre(FILE* fichier)
{
     char c;
     fscanf(fichier, "%c", &c);
     return c;
}

int aller_fin_de_ligne(FILE* fichier)
{
      while(lire_lettre(fichier)!='\n') {}
      return 2;
}

int charger_maille(char* nom_du_fichier, Maille* maille);
{
    FILE* fichier = ouvrir_fichier(nom_du_fichier);
    detection_mot(fichier,cell_leng)



    fermeture_fichier(fnom_du_fichier);
}

void fermeture_fichier(FILE* nom_du_fichier)
{
    fclose(nom_du_fichier);
}
