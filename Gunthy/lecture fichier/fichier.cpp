#include "fichier.h"

FILE* ouvrir_fichier(char* nom_du_fichier)
{
    return fopen(nom_du_fichier, "r");
}

char lire_lettre(FILE* fichier)
{
     char c;
     fscanf(fichier, "%c", &c);
     return c;
}

int aller_prochaine_commande(FILE* fichier)
{
      while(lire_lettre(fichier)!='_') {}
      return 2;
}

int charger_maille(char* nom_du_fichier, Maille* maille)
{
    FILE* fichier = ouvrir_fichier(nom_du_fichier);
    if(fichier == NULL)
        return ERR_OUVERTURE_FICHIER;

    automate(fichier, maille);

    fermeture_fichier(fichier);
    return 0;
}

void fermeture_fichier(FILE* nom_du_fichier)
{
    fclose(nom_du_fichier);
}

int detection_mot(FILE* fichier, char* a_detecter)
{
    int i = 0;
    int retour = 1; // trouve , non fin de ligne
    char caractere = -1;

    while(retour == 1 && a_detecter[i] != '\0')
    {
        caractere = lire_lettre(fichier);
        if(caractere == '_')   // nouvelle commande
        {
            retour = 2;
        }
        else if(caractere  != a_detecter[i])
        {
            retour = 0;
        }
        else if(caractere != ' ')
            i++;
    }

    return retour;
}

int detection_reel(FILE* fichier, double* reel)
{
    double virgule = 0;
    *reel = 0;
    int retour = 0; // Non trouve, non fin de ligne
    char caractere = 0;
    int sortie = 0;

    while(!sortie)
    {
       caractere = lire_lettre(fichier);
       // 4 cas : chiffre, virgule, fin de ligne, autre
       if(caractere == '_')
       {
           retour+= 2;
           sortie = 1;
       }
       else if(caractere == '.')
       {
            if(virgule == 0)
                virgule = 1;
            else
            {
                sortie = 1; // On sort de la, pas de deux virgules
            }
       }
       else if(caractere>= 48 && caractere<= 57)// un chiffre
       {
            retour = 1; // on a au moins un chiffre
            double chiffre = (double) (caractere - 48);
            if(virgule == 0)
            {
                *reel = (*reel) * 10 + chiffre;
            }
            else
            {
                virgule /= 10;
                *reel += (chiffre * virgule);
            }
       }
       else // le nawak
       {
            if(retour == 1) // on a detecte au moins un chiffre
            {
                sortie = 1; // On sort de la
            }
       }
    }

    return retour;
}

int automate(FILE* fichier, Maille* maille)
{
    int etat = ATTENTE_NVELLE_COMMANDE;
    int retour; // retour de detection mot
    char c = 0;

    while (etat != FIN_FICHIER)
    {
        switch(etat)
        {
            case NOUVELLE_COMMANDE:                         // l'underscore est passe, toute nouvelle commande
                c = lire_lettre(fichier);

                switch(c)
                {


                    case EOF :
                        etat = FIN_FICHIER;
                    break;


                    case 'c' :
                        retour = detection_mot(fichier, "ell");
                        if(retour%4 == 0)
                            etat = ATTENTE_NVELLE_COMMANDE;
                        else if(retour%4 == 1)
                        {
                            aller_prochaine_commande(fichier);
                            etat = CELL;
                        }
                        else if(retour%4 == 2)
                            etat = NOUVELLE_COMMANDE;
                        else
                            etat = CELL;

                        if(retour/4 == 1) // End of file
                            etat = FIN_FICHIER;
                    break;


                    case 's' :
                        retour = detection_mot(fichier, "ymmetry");
                        if(retour%4 == 1)

                             etat = ATTENTE_NVELLE_COMMANDE;
                        else if(retour%4 == 1)
                        {
                            aller_prochaine_commande(fichier);
                            etat = SYMMETRY;
                        }
                        else if(retour%4 == 2)
                            etat = NOUVELLE_COMMANDE;
                        else
                            etat = SYMMETRY;

                        if(retour/4 == 1) // End of file
                            etat = FIN_FICHIER;
                    break;


                    case 'a' :
                        retour = detection_mot(fichier, "tome");
                        if(retour%4 == 1)

                             etat = ATTENTE_NVELLE_COMMANDE;
                        else if(retour%4 == 1)
                        {
                            aller_prochaine_commande(fichier);
                            etat = ATOME;
                        }
                        else if(retour%4 == 2)
                            etat = NOUVELLE_COMMANDE;
                        else
                            etat = ATOME;

                        if(retour/4 == 1) // End of file
                            etat = FIN_FICHIER;
                    break;



                    default :
                        etat = ATTENTE_NVELLE_COMMANDE;
                }
            break;


         case CELL:
            c = lire_lettre(fichier);
              if (c != '_')
             {etat = NOUVELLE_COMMANDE;}


              else
              {

               c = lire_lettre(fichier);
                switch (c)


                case 'a' :
                    retour = detection_mot(fichier, "ngle");
                    if(retour%4 == 1)

                                 {etat = ATTENTE_NVELLE_COMMANDE;}
                    else if(retour%4 == 1)
                            {
                                aller_prochaine_commande(fichier);
                                etat = CELL_ANGLE;
                            }
                    else if(retour%4 == 2)
                                etat = NOUVELLE_COMMANDE;
                    else
                                etat = CELL_ANGLE;

                    if(retour/4 == 1) // End of file
                                etat = FIN_FICHIER;
                break;


                case 'l' :
                    retour = detection_mot(fichier, "ength");
                    if(retour%4 == 1)

                                 etat = ATTENTE_NVELLE_COMMANDE;
                    else if(retour%4 == 1)
                            {
                                aller_prochaine_commande(fichier);
                                etat = CELL_LENGTH;
                            }
                    else if(retour%4 == 2)
                                etat = NOUVELLE_COMMANDE;
                    else
                                etat = CELL_LENGTH;

                    if(retour/4 == 1)                            // End of file
                                etat = FIN_FICHIER;
                break;


                default :
                        etat = ATTENTE_NVELLE_COMMANDE;

                break;
            }
            break;                                       //fermeture case CELL



        case CELL_LENGTH:
            c = lire_lettre(fichier);

              if (c != '_')
             {etat = NOUVELLE_COMMANDE;}


              else
              { c = lire_lettre(fichier);

                switch (c)  {
                    case 'a' :
                        retour=detection_reel(fichier, &(maille->a));
                        if(retour%4 == 1)

                                     etat = ATTENTE_NVELLE_COMMANDE;
                        else if(retour%4 == 1)
                                {
                                    aller_prochaine_commande(fichier);
                                    etat = NOUVELLE_COMMANDE;
                                }
                        else if(retour%4 == 2)
                                    etat = NOUVELLE_COMMANDE;

                        if(retour/4 == 1)                            // End of file
                                    etat = FIN_FICHIER;
                    break;

                }






              }

        }
    }

    return 0;
}
