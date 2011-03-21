#include "fichier.h"

void ouvrir_maille (char* fichier)
{FILE* cif = NULL;
    cif=fopen("fichier.cif", "r");
    return 0;
};



double* lecture_cell_length_a (char* fichier) {
 double* r=NULL;
r=strstr( char* fichier, "_cell_length_a");
return r;

    };





double valeur_cell_length_a (char* fichier,double* lecture_cell_length_a)
  double num;


{if lecture_cell_length_a != 0  {


}

else{puts "erreur, longueur du vecteur a introuvable"}
}
