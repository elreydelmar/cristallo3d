#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


#include "main.h"
#include "fonction.h"


using namespace std;

int main()
{
    grille grillin;
    grille GrilleResolue;
    int ok=0;
    int infi=0;
    int Difficulte=0;


    printf("\t  Calculs en cours . . .");

    //exit(EXIT_FAILURE);
    // CREATION GRILLE
    do
    {
        ok = CreationGrille(&grillin);
        infi++;

        if (infi >= 2)
        {
            printf("\n\n\n**** ERREUR NOMBRE DE GRILLES GENEREES MAXIMUMUM ET PAS DE RESULTAT ****\n\n");
            exit(EXIT_FAILURE);
        }
    }while(ok!=1);




    cout << "\n\n\n\n\tL'ordinateur l a fait! ouah TROP BIEN\n" << endl;
    printf("\n\nNombre de tentatives necessaires : %d\n",infi);

    GrilleResolue = grillin;



    cout << "Hello world!\n\n\n" << endl;
    printf("\n\n Veuillez donner le niveau de difficulte (1 2 ou 3) :");
    scanf("%d",&Difficulte);
    infi =0;
    ok = 0;

    //VIDAGE ET PREPARATION GRILLE
    do
    {
        ok = PreparationGrille(&grillin, &Difficulte);
        infi++;

        if (infi >= 2)
        {
            printf("\n\n\n**** ERREUR LA PREPARATION DE LA GRILLE A ECHOUE ****\n\n");
            exit(EXIT_FAILURE);
        }
    }while(ok!=1);





    return 0;
}
