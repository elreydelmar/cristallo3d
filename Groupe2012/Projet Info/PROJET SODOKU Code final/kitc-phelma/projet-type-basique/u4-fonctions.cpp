// u4-fonctions.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
#include <stdlib.h>     // exit, rand
#include <stdio.h>
#include <time.h>       // time
#include <string.h>     // strcpy
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
// Programmes locaux
#include "u1-interface.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;

// Initialiser
void InitialiserDonnees()
{
    // On initialise le generateur de nombres aleatoires
    srand(time(NULL));

}






// Fonctions

// AJOUT DE CAKE M
int TrouveCarre(int NumCase)
    {
        int k = 0, l = 0,  NumCarre = 0;
        int j = 0;

     // Calcul de la ligne et colonne de la case
        NumCase++;

        k = NumCase % 9;        // k : Colonne où est située la case
        j = NumCase/9;
            if ( NumCase%9 != 0)
                {
                    l = j+1;
                }
            else {l = j;}       // l : ligne où est située la case

            //printf(" l = %d",l);

      //  Calcul du carré en fonction de ça...
            if (k==1 || k==4 || k==7)
                {
                    if (l==1 || l==4 || l==7  )
                        {
                            NumCarre = NumCase;
                        }
                    else if (l==2 || l==5 || l==8 )
                        {
                            NumCarre = NumCase - 9;
                        }
                    else
                        {
                            NumCarre = NumCase - 18;
                        }
                }
            else if (k==2 || k==5 || k==8)
                {
                    if (l==1 || l==4 || l==7  )
                        {
                            NumCarre = NumCase - 1;
                        }
                    else if (l==2 || l==5 || l==8 )
                        {
                            NumCarre = NumCase - 10;
                        }
                    else
                        {
                            NumCarre = NumCase - 19;
                        }
                }

            else
                {
                 if (l==1 || l==4 || l==7  )
                        {
                            NumCarre = NumCase - 2;
                        }
                    else if (l==2 || l==5 || l==8 )
                        {
                            NumCarre = NumCase - 11;
                        }
                    else
                        {
                            NumCarre = NumCase - 20;
                        }
                }


        return NumCarre;
    }









/*
int TestCase(grille *grillin, int NumCase)
{
    int i = 0, m = 0;
    int Preums =0;

    for (i=0; i<81; i++)    //Boucle pour tous les chiffres du tableau
    {

        NumCase = grillin->table[i]; // le numéro de la case du nombre qu'on étudie (tableau vu en ligne)
        Carre carre;                    //un carré de 9, dans lequel est notre nombre...


        Preums = TrouveCarre(NumCase);  // première case du carré contenant la case permettant de calculer les autres...
        carre.Cases[1] = Preums + 1;
        carre.Cases[2] = Preums + 2;
        carre.Cases[3] = Preums + 9;
        carre.Cases[4] = Preums + 10;
        carre.Cases[5] = Preums + 11;
        carre.Cases[6] = Preums + 18;
        carre.Cases[7] = Preums + 19;
        carre.Cases[8] = Preums + 20;



        for (m=1; m<10; m++ )                   // Vérification en tant que tel...
            {
                if(NumCase==carre.Cases[m])
                    {
                        return 1;
                    }

                else {return 0;}
            }
    }

    return -1;
}
*/



int TestCase(grille * grillin, int NumCase, int Nbre, int Increment )
{
    int Preums=0;
    //printf("TEEEEEEEEEEEEEEEEEEEEEEEEEST %d", NumCase + 9*Increment);
    Preums = TrouveCarre(NumCase + 9*Increment);
    Preums --;
    //printf("Trouver case : %d", Preums);
    if (Nbre-grillin->table[Preums] == 0 || Nbre-grillin->table[Preums+1]==0 || Nbre-grillin->table[Preums+2]==0 || Nbre-grillin->table[Preums+9]==0 || Nbre-grillin->table[Preums+10]==0 || Nbre-grillin->table[Preums+11]==0 || Nbre-grillin->table[Preums+18]==0 || Nbre-grillin->table[Preums+19]==0 || Nbre-grillin->table[Preums+20]==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}




/*


int TestColonne(grille *grillin, int NumCase)
{
    int i, j, k = 0;

    for (i=0; i<81; i++)                    // boucle sur tous les nombres du tableau
    {
        NumCase = grillin->table[i];


        for (k=1; k<10; k++)
                {
                    if (grillin->table [i] - 9*k <= 0 || grillin->table [i] + 9*k >= 10) // Si jamais ça dépasse
                    {
                        k = 0;                          //Je voudrais que ça annule le reste mais chuis pas sûr que ça le fasse ?,:p
                    }

                    else
                    {
                      for(j=1; j<10; j++)  //On compare avec les autres de la colonne

                      {
                        if (grillin->table [i] - 9*k == j || grillin->table [i] + 9*k == j)
                            {
                                return 1;
                            }
                        else
                            {
                                return 0;
                            }
                      }

                    }

                }

    }




    return -1;
}


*/

// FIN AJOUT DE CAKEM


int TestColonne(grille *grillin, int alea1, int Nbre, int Increment)
{
    int i,j;

    for(i=Increment;i>0;i--)
    {
        if (Nbre - grillin->table[alea1 + 9*Increment - 9*i] == 0)
        {
            return 0;
        }
    }

    for(j=Increment;j<8;j++)
    {
        if (Nbre - grillin->table[alea1 + 9*Increment + 9*j] == 0)
        {
            return 0;
        }
    }


    return 1;
}



// JE PENSE QU'IL Y A DES BUGS

int TestLigne(grille *grillin, int alea1, int Nbre, int Increment)
{
    int i,j;

    for(i=alea1-1;i>9*Increment-1;i--)
    {
        if (Nbre - grillin->table[i] == 0)
        {
            return 0;
        }
    }

    for(j=alea1+1;j<9*Increment+9;j++)
    {
        if (Nbre - grillin->table[j] == 0)
        {
            return 0;
        }
    }


    return 1;
}




void CreationGrille(grille *grillin)
{
    srand(time(NULL));
    int alea1=0;
    int i=0;
    int j=0;
    int k=0;
    int compteur=1;
    int Col=-1;
    int Car=-1;
    int sortir=0;
    int infi3=0;
    int infi2=0;

    for (j=0; j<81 ; j++)
    {
        grillin->table [j]=0;
    }
/*
    for (j=0; j<81 ; j++)
    {
        printf("%d", grillin->table [j]);
    }
*/

    for (i=0; i<9 ; i++)
    {

        //printf("On passe a la %d ligne ------------------------------------------------",i);

        for (k=1; k<10 ; k++)
        {
            alea1 = rand ()%9;
            //alea1 = alea1 +1;

            //printf("%d",alea1);


            sortir = 0;
            do
            {
                if (grillin->table [alea1 + 9*i] == 0)
                {
                    // test
                    Col = TestColonne(grillin, alea1, k, i);
                    /*printf("Col = %d",Col);
                    if (Col == 0)
                    {
                        printf("**************COL**************\n");
                    }*/
                    //test

                    //test trouver carre
                    Car = TestCase (grillin, alea1, k, i);
                    /*printf("\n`Car = %d",Car);
                    if (Car == 0)
                    {
                        printf("**************CAR**************\n");
                    }*/
                    // test

                    // BUG A PREVOIR SUR CETTE IF
                    if (Col==1 && Car==1)
                    {
                        grillin->table [alea1 + 9*i] = k;
                        sortir=1;
                        //printf("\n\n");
                    }
                    else
                    {
                        infi3 ++;
                        alea1 = rand ()%9;
                        //alea1 = alea1 + 1;
                        if (alea1 ==9)
                        {
                            alea1 = 0;
                        }
                    }

                }
                else
                {
                    infi3 ++;
                    alea1 = rand ()%9;
                    //alea1 = alea1 + 1;
                    if (alea1 ==9)
                    {
                        alea1 = 0;
                    }
                }


                if (infi3 >= 80)
                {
                    //printf("********************* ERREUR DE BOUCLE INFINI **********************");
                    //return 0;
                    for (j=0; j<9 ; j++)
                    {
                        grillin->table [j + 9*i] = 0;
                    }
                    sortir = 1;
                    k=0;
                    infi2 ++;

                    if (infi2 >= 60)
                    {
                        //printf("********************* ERREUR DE BOUCLE INFINI **********************");
                        //return 0;
                        for (j=0; j<9 ; j++)
                        {
                            grillin->table [j + 9*i] = 0;
                        }
                        for (j=0; j<9 ; j++)
                        {
                            grillin->table [j + 9*(i-1)] = 0;
                        }
                        sortir = 1;
                        k=0;
                        i--;


                    }

                }



            } while (sortir ==0);

            infi3 =0;

            // TEST AFFICHAGE ENLEVER DES COMMENTAIRES SI ON VEUT VOIR LE DEROULEMENT DE LA GENERATION DE LA GRILLE
            /*
            printf("\n\n");
            for (j=0; j<81 ; j++)
            {

                printf("%d", grillin->table [j]);
                compteur ++;
                if (compteur==10)
                {
                    printf("\n");
                    compteur = 1;
                }

            }
            */








            alea1 = 0;
        }




        k=0;
        infi2 = 0;
        // grillin->table [alea2] = alea1;
        // printf("chiffre dans la table : %d\n", grillin->table [alea2]);


    }


    printf("\n\n\n\n");
    for (j=0; j<81 ; j++)
    {
        printf("%d", grillin->table [j]);
        compteur ++;
        if (compteur==10)
        {
            printf("\n");
            compteur = 1;
        }

    }

    //return 1;

}


void PreparationGrille(grille * grillin, int Difficulte)
{
    // Nombre de chiffres retirés
    int NbreChiffresRetires=0;

    switch (Difficulte) {
    case (1) :
        NbreChiffresRetires=40;
        break;
    case (2) :
        NbreChiffresRetires=48;
        break;
    case (3) :
        NbreChiffresRetires=56;
        break;
    }


    //Declarations
    int i=0;
    srand(time(NULL));
    int alea=0;
    int compteur=1;
    int j=0;
    int temp=0;
    int doublon=0;



    for(i=1; i<(NbreChiffresRetires/2)+1; i++)
    {
        do
        {
            alea = rand ()%81;
            if (grillin->table [alea] != 0)
            {
                grillin->table [alea] = 0;
                grillin->table [80-alea] = 0;
                doublon=0;
            }
            else
            {
                doublon=1;
            }

        } while (doublon!=0);


    }


    printf("\n\nGrille Preparee\n\n");
    for (j=0; j<81 ; j++)
    {
        if (grillin->table [j] == 0)
        {
            printf(".");
            temp++;
        }
        else
        {
            printf("%d", grillin->table [j]);
        }

        compteur ++;
        if (compteur==10)
        {
            printf("\n");
            compteur = 1;
        }

    }
    printf("\n\n\n");


    printf("Nombre de chiffres retires : %d", NbreChiffresRetires);
    printf("\nNombre de chiffres retires pour de vrai: %d\n", temp);
}


void NouvelleGrille ()
{

}

void VerifSolution ()
{

}

// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds )
{
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}


grille grillin;
grille GrilleResolue;
grille GrilleTemp;

int PosX;
int PosY;

