#include "fichier.h"

void ouvrir_fichier(char* nom_du_fichier)
{
    FILE* cif = NULL;
    cif=fopen("fichier.cif", "r");
    return cif;
}


char lire_lettre(FILE* nom_du_fichier)
 fprintf()




void fermeture_fichier(FILE* nom_du_fichier)
{
    fclose(nom_du_fichier);

}
