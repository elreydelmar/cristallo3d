#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fichier.h"
#include "structures.h"

FILE* ouvrir_fichier(char* nom_du_fichier)
{
    return fopen(nom_du_fichier, "r");
}

char lire(FILE* fichier)
{
     char c = fgetc(fichier);
     return c;
}

void fermeture_fichier(FILE* nom_du_fichier)
{
    fclose(nom_du_fichier);
}


int main ()
{  FILE* fichier=NULL; /*creation d un fichier memoire de type FILE */
    int a=0; /* variable : caractere lu */
    int nb_sommets;
    int nb_arcs;
    fichier= ouvrir_fichier("graphe2.txt"); /* correspondance entre le fichier de type file* et le fichier graphe1.txt a ouvrir*/
    if (fichier != NULL)
        {
            fscanf(fichier, "%d", &nb_sommets);
            fscanf(fichier, "%d", &nb_arcs);
            sommet* tab_sommet=(sommet*)calloc(nb_sommets, sizeof(sommet));
            char* s=(char*)calloc(18, sizeof (char)); /*on cree la chaine de caractere qui contient sommet du graphe lu dans le fichier*/
            while (fgetc(fichier) != '\n');
            fgets(s, 18, fichier);

            if (strcmp("Sommets du graphe",s)==1)
                {
                     printf ("erreur dans le fichier sommet_du_graphe\n");
                     printf ("%s",s);

                }

            else
                {   int num=0;

                    (*(*tab_sommet)).numero=num;
                        printf("%p",tab_sommet);                 //   fscanf(fichier,"%d",&num);
                 //   fscanf(fichier,"%d",&num); /* adresse de num */
                 //   (*tab_sommet)->numero=num;

                    printf("%d",num);
                }





        }
}




/* ligne 34 ou ligne 49, mais a priori cest la ligne 34 au niveau de lallocation*/
