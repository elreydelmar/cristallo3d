#include "fichier.h"

int main ()
{
    FILE* fichier;
    fichier=ouvrir_fichier("nimps.cif")  ;                  /*lecture de cell*/


    fermeture_fichier(fichier);
}
