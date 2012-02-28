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
    char nom_fic[N];
    float a=0, b=0, c=0, alpha=0, beta=0, gamma=0;
    char *nom_auteur, *form_chim, *sym_space, *sym_xyz;
    float vol=0;
    char choix='o', rec='o', rec2='o';
    char *nom_atome;
    float x=0, y=0, z=0;

    // Allocation dynamique tableau carac pointeur
    nom_auteur = (char*) malloc (30 * sizeof(char));
    form_chim = (char*) malloc (30 * sizeof(char));
    sym_space = (char*) malloc (30 * sizeof(char));
    //choix = (char*) malloc (2 * sizeof(char));
    //rec = (char*) malloc(2 * sizeof(char));
    sym_xyz = (char*) malloc (20 * sizeof(char));

    // Bla bla qui sert à rien
    cout << "Bonjour, bienvenue dans la creation de la maille!\n" << endl;
    printf("Veuillez entrer le nom de la maille :");
    scanf(" %s",nom_fic);
    strcat(nom_fic, ".cif");
    FILE * fichier = fopen(nom_fic,"w");
    if(fichier == NULL) // Test ouverture canal
    {
        printf ("ERREUR FICHIER NON CREE");
        return -1;
    }


    fprintf(fichier, "# Fichier maille personnelle cree a partir du logiciel cristallo 3D\n# GRENOBLE INP PHELMA\n#####################################################################\n");

    fprintf(fichier, "loop_\n");// Init loop

    // Nom auteur
    printf ("Auteur :");
    scanf(" %s",nom_auteur);
    fprintf(fichier, "_publ_author_name\n'%s'", nom_auteur);

    // Formule chimique
    printf("Formule chimique :");
    scanf(" %s", form_chim);
    fprintf(fichier, "_chemical_formula_sum           '%s'\n", form_chim);

    // _symmetry_space_group_name_H-M
    printf("Groupe d espace :");
    scanf(" %s", sym_space);
    fprintf(fichier, "_symmetry_space_group_name_H-M   '%s'\n", sym_space);




    // alpha, beta gamma
    printf("alpha:");
    scanf("%f",&alpha);
    fprintf(fichier, "_cell_angle_alpha                %f\n",alpha);

    printf("beta:");
    scanf("%f",&beta);
    fprintf(fichier, "_cell_angle_beta                %f\n",beta);

    printf("gamma:");
    scanf("%f",&gamma);
    fprintf(fichier, "_cell_angle_gamma                %f\n",gamma);



    // a, b c
    printf("a:");
    scanf("%f",&a);
    fprintf(fichier, "_cell_length_a                   %f\n",a);

    printf("b:");
    scanf("%f",&b);
    fprintf(fichier, "_cell_length_b                   %f\n",b);

    printf("c:");
    scanf("%f",&c);
    fprintf(fichier, "_cell_length_c                   %f\n",c);

    vol = a*b*c;
    fprintf(fichier, "_cell_volume                     %f\n",vol);


    // symetries
    fprintf(fichier, "loop_\n");
    fprintf(fichier, "_symmetry_equiv_pos_as_xyz\n");
    fprintf(fichier, "x,y,z\n");
    printf("position de symetries du type : x,y,z (entree)\n");
    printf(" x,y,z a deja ete rentre. Voulez vous entrer d autres symetries: o/n");

    //fgets(choix, 2, stdin);
    scanf(" %c", &choix);

    if (choix == 'o')
    {
        do
        {
            printf("Veuillez entrer position de symetries du type : x,y,z (entree)");
            scanf(" %s", sym_xyz);
            fprintf(fichier,"%s\n", sym_xyz);

            printf("Rentrer une autre position? o/n");
            //fgets(rec, 2, stdin);
            scanf(" %c", &rec);
        }
        while(rec == 'o');
    }
    else (printf("Les symetries n ont pas ete rentrees\n"));



    // loop et position particulieres
    fprintf(fichier, "loop_\n");
    fprintf(fichier, "_atom_site_label\n");
    fprintf(fichier, "_atom_site_fract_x\n");
    fprintf(fichier, "_atom_site_fract_y\n");
    fprintf(fichier, "_atom_site_fract_z\n");
    fprintf(fichier, "_atom_site_U_iso_or_equiv\n");

    printf("Position des atomes particuliers du type : Na 0.00000 0.00000 0.00000 (entree)\n");


    do
    {
        printf("Veuillez entrer position des atomes\n");
        printf("nom atome :");
        scanf(" %s", nom_atome);
        fprintf(fichier,"%s ", nom_atome);

        printf("x :");
        scanf("%f",&x);
        fprintf(fichier,"%f \n", x);

        printf("y :");
        scanf("%f",&y);
        fprintf(fichier,"%f \n", y);

        printf("z :");
        scanf("%f",&z);
        fprintf(fichier,"%f \n", z);

        fprintf(fichier,"0.0000\n");



        printf("Rentrer une autre position? o/n ");
        //fgets(rec2, 2, stdin);
        scanf(" %c", &rec2);

    }while(rec2 == 'o');



    fprintf(fichier,"\n");
    // Fin du fichier
    printf ("Maille personnelle creee\n\n");
    fclose(fichier);

 /*
    char * name;
    name = (char*) malloc (30 * sizeof(char));
    printf("name : \n");
    fgets(name, 30, stdin);
    printf("%s",name);
*/













    return 0;
}
