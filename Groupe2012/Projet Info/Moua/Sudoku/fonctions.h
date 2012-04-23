int TrouveCarre(int NumCase)
    {
        int k = 0, l = 0,  NumCarre = 0;
        int j = 0;

     // Calcul de la ligne et colonne de la case

        k = NumCase % 9;        // k : Colonne où est située la case
        j = NumCase/9;
            if ( j%9 != 0)
                {
                    l = j+1;
                }
            else {l = j;}       // l : ligne où est située la case


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


        return Numcarre;
    }










int TestCase(grille *grillin, int NumCase)
{
    int i = 0, j = 0, k = 0, m = 0;

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
                if(Numcase==Carre.Cases[m])
                    {
                        return 1;
                    }

                else {return 0;}
            }
    }


}








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





}
