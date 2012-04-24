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


    //exit(EXIT_FAILURE);
    do
    {
        ok = CreationGrille(&grillin);
        infi++;
        if (infi >= 10000000)
        {
            printf("**** ERREUR NOMBRE DE GRILLES GENEREES MAXIMUMUM ET PAS DE RESULTAT ****");
            exit(EXIT_FAILURE);
        }
    }while(ok!=1);




    cout << "\n\n\n\n\tL'ordinateur l a fait! ouah TROP BIEN\n" << endl;
    printf("\n\nNombre de tentatives necessaires : %d",infi);



    cout << "Hello world!" << endl;
    return 0;
}
