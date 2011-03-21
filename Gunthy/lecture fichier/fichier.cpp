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

int aller_fin_de_ligne(FILE* fichier)
{
      while(lire_lettre(fichier)!='\n') {}
      return 2;
}

int charger_maille(char* nom_du_fichier, Maille* maille)
{
    FILE* fichier = ouvrir_fichier(nom_du_fichier);
    if(fichier == NULL)
        return ERR_OUVERTURE_FICHIER;

    while(nouvelle_ligne(fichier, maille)) {}  // Nouvelle ligne renvoie 0 si end of file

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
        if(caractere == '\n')   // Fin de ligne
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
       if(caractere == '\n')
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
