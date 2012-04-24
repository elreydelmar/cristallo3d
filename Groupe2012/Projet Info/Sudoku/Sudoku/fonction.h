




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

            printf(" l = %d",l);

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




int TestCase(grille * grillin, int NumCase, int Nbre, int Increment )
{
    int Preums=0;
    printf("TEEEEEEEEEEEEEEEEEEEEEEEEEST %d", NumCase + 9*Increment);
    Preums = TrouveCarre(NumCase + 9*Increment);
    printf("Trouver case : %d", Preums);


    return 1;
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



void CreationGrille(grille *grillin)
{
    srand(time(NULL));
    int alea1=0;
    int alea2=0;
    int i=0;
    int j=0;
    int k=0;
    int compteur=1;
    int Col=-1;
    int Car=-1;

    for (j=0; j<81 ; j++)
    {
        grillin->table [j]=0;
    }

    for (j=0; j<81 ; j++)
    {
        printf("%d", grillin->table [j]);
    }


    for (i=0; i<9 ; i++)
    {

        alea1 = rand ()%8;
        alea1 ++ ;
        alea2 = rand ()%80;

        int sortir=0;


        printf("alea1 : %d\n", alea1);
        printf("alea2 : %d\n", alea2);


        printf("On passe a la %d ligne -----------",i);

        for (k=1; k<10 ; k++)
        {
            alea1 = rand ()%8;
            //alea1 = alea1 +1;
            printf("%d",alea1);




             /*
            //TEST ajout cake
            Col = TestColonne (grillin, alea1);
            printf("Col = %d",Col);
            Car = -1;
            printf("Car = %d",Car);
             */

            // Test moi
            /*
            Col = TestColonne(grillin, alea1, k, i);
            printf("Col = %d",Col);
            */


            sortir = 0;
            do
            {
                if (grillin->table [alea1 + 9*i] == 0)
                {
                    // test
                    Col = TestColonne(grillin, alea1, k, i);
                    printf("Col = %d",Col);
                    if (Col == 0)
                    {
                        printf("****************************\n");
                    }
                    //test

                    //test trouver carre
                    Car = TestCase (grillin, alea1, k, i);



                    grillin->table [alea1 + 9*i] = k;
                    sortir=1;
                    printf("\n\n");
                }
                else
                {
                   alea1 = alea1 + 1;
                   if (alea1 ==9)
                   {
                        alea1 = 0;
                    }
                }

            } while (sortir ==0);


            // Test affichage
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




            alea1 = 0;
        }





        // grillin->table [alea2] = alea1;
        // printf("chiffre dans la table : %d\n", grillin->table [alea2]);


    }


    printf("\n\n\n");
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

}
