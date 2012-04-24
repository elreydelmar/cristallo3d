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
    int ok=0;
    int infi=0;

    printf("\t  Calculs en cours . . .");

    //exit(EXIT_FAILURE);
    do
    {
        ok = CreationGrille(&grillin);
        infi++;
        if (infi >= 1000000000)
        {
            printf("\n\n\n**** ERREUR NOMBRE DE GRILLES GENEREES MAXIMUMUM ET PAS DE RESULTAT ****\n\n");
            exit(EXIT_FAILURE);
        }
    }while(ok!=1);




    cout << "\n\n\n\n\tL'ordinateur l a fait! ouah TROP BIEN\n" << endl;
    printf("\n\nNombre de tentatives necessaires : %d\n",infi);



    cout << "Hello world!\n\n\n" << endl;
    return 0;
}
