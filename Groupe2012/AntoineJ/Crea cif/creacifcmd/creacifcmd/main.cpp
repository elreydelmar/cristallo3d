#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define N 200

using namespace std;

int main()
{
    // Déclarations
    char nom_fic;
    float a=0;
    char *nom_auteur, *form_chim, *sym_space;

    // Allocation dynamique tableau carac pointeur
    nom_auteur = (char*) malloc (30 * sizeof(char));
    form_chim = (char*) malloc (30 * sizeof(char));
    sym_space = (char*) malloc (30 * sizeof(char));

    // Bla bla qui sert à rien
    cout << "Bonjour, bienvenue dans la creation de la maille!\n" << endl;
    printf("Veuillez entrer le nom de la maille:");
    scanf("%s",&nom_fic);
    strcat(&nom_fic, ".cif");
    FILE * fichier = fopen(&nom_fic,"w");
    if(fichier == NULL) // Test ouverture canal
    {
        printf ("ERREUR FICHIER NON CREE");
        return -1;
    }


    fprintf(fichier, "# Fichier maille personnelle cree a partir du logiciel cristallo 3D\n# GRENOBLE INP PHELMA\n#####################################################################\n");

    fprintf(fichier, "loop_\n");// Init loop

    // Nom auteur
    printf ("Auteur :");
    fgets(nom_auteur, 30, stdin);
    fprintf(fichier, "_publ_author_name\n'%s'", nom_auteur);

    // Formule chim
    printf("Formule chimique :");
    fgets(form_chim, 30, stdin);
    fprintf(fichier, "_chemical_formula_sum           '%s'\n", &form_chim);

    // _symmetry_space_group_name_H-M





    printf("a:");
    scanf("%f",&a);
    fprintf(fichier, "a = %f",a);
    printf ("Maille personnelle creee\n\n");
    fclose(fichier);


    char * name;
    name = (char*) malloc (30 * sizeof(char));
    printf("name : \n");
    fgets(name, 30, stdin);
    printf("%s",name);














    return 0;
}
