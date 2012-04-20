

// Prototype
// void CreationGrille(grille);










// Fonctions

void CreationGrille(grille *grillin)
{
    srand(time(NULL));
    int alea1=0, alea2=0;
    int i=0;
    int j=0;
    int k=0;

    for (j=0; j<80 ; j++)
    {
        grillin->table [j]=0;
    }

    for (j=0; j<80 ; j++)
    {
        printf("%d", grillin->table [j]);
    }


    //for (i=1; i<10 ; i++)
    //{
        alea1 = rand ()%8;
        alea1 ++ ;
        alea2 = rand ()%80;
        int sortir=0;

        printf("alea1 : %d\n", alea1);
        printf("alea2 : %d\n", alea2);

        for (k=1; k<10 ; k++)
        {
            alea1 = rand ()%8;
            //alea1 = alea1 +1;
            sortir = 0;
            do
            {
                if (grillin->table [alea1 + i] == 0)
                {
                    grillin->table [alea1 + i] = k;
                    sortir=1;
                    printf("\n\n");
                }
                else
                {
                   alea1 = alea1 + 1;
                   if (alea1 ==10)
                   {
                        alea1 = 0;
                    }
                }

            } while (sortir ==0);

            for (j=0; j<80 ; j++)
            {
                printf("%d", grillin->table [j]);
            }


        }




        // grillin->table [alea2] = alea1;
        // printf("chiffre dans la table : %d\n", grillin->table [alea2]);


    //}

    for (j=0; j<80 ; j++)
    {
        printf("%d", grillin->table [j]);
    }

}
