#include "fichier.h"

FILE* ouvrir_fichier(char* nom_du_fichier)
{
    return fopen(nom_du_fichier, "r");
}

char lire_lettre(FILE* fichier)
{
/*
    static int fin = 0;
    if(fin == 29025)
        return EOF;
    else
        fin++;
*/
     char c;
     fscanf(fichier, "%c", &c);
     printf("%c", c);
     return c;
}

int aller_prochaine_commande(FILE* fichier)
{
    char c = lire_lettre(fichier);
    while(c !='_' && c != EOF)
        c = lire_lettre(fichier);

    return (c == '_') ? 2 : 6;  // Nouvelle commande ou fin du fichier
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

int detection_mot(FILE* fichier, const char* a_detecter)
{
    int i = 0;
    int retour = 1; // trouve , non fin de ligne
    char caractere = -1;

    while(retour%4 == 1 && a_detecter[i] != '\0')
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
        else if(caractere == EOF)
            retour = 4;
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
       // 5 cas : chiffre, virgule, nouvelle commande, EOF, autre
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
       else if(caractere == EOF)
       {
           retour += 4; // bye bye
           sortie = 1;
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
            case ATTENTE_NVELLE_COMMANDE :
                if(aller_prochaine_commande(fichier) == 2)
                    etat = NOUVELLE_COMMANDE;
                else
                    etat = FIN_FICHIER;
            break;

            case NOUVELLE_COMMANDE:           // l'underscore est passe, toute nouvelle commande
                etat_nouvelle_commande(fichier, maille, &etat, &retour, &c);
            break;

            case CELL :
                etat_cell(fichier, maille, &etat, &retour, &c);
            break;

            case CELL_LENGTH:
                etat_cell_length(fichier, maille, &etat, &retour, &c);
            break;

            default :
                etat = ATTENTE_NVELLE_COMMANDE;
            break;
        }

    }

    return 0;   // A CHANGER
}

void traiter_sous_commande(FILE* fichier, Maille* maille, int* etat, int* retour, char* c, const char* a_detecter, int etat_a_atteindre)
{
    *retour = detection_mot(fichier, a_detecter);
    if(*retour/4 == 1) // End of file
    {
        *etat = FIN_FICHIER;
        return;
    }

    if(*retour%4 == 0)       // Non trouve non fin de ligne : cas classique 1
        *etat = ATTENTE_NVELLE_COMMANDE;
    else if(*retour%4 == 1) // Trouve et non fin de ligne
    {
        if(aller_prochaine_commande(fichier) == 2)
            *etat = etat_a_atteindre;
        else
            *etat = FIN_FICHIER;
    }
    else if(*retour%4 == 2)                 // Non trouve mais on a passe l underscore
        *etat = NOUVELLE_COMMANDE;
    else
        *etat = etat_a_atteindre;           // On a trouve et passe l underscore : cas classique 2
}

void etat_nouvelle_commande(FILE* fichier, Maille* maille, int* etat, int* retour, char* c)
{
    *c = lire_lettre(fichier);
    switch(*c)
    {
        case EOF :
            *etat = FIN_FICHIER;
        break;

        case 'c' :
            traiter_sous_commande(fichier, maille, etat, retour, c, "ell", CELL);
        break;

        case 's' :
            traiter_sous_commande(fichier, maille, etat, retour, c, "ymmetry", SYMMETRY);
        break;

        case 'a' :
            traiter_sous_commande(fichier, maille, etat, retour, c, "tome", ATOME);
        break;

        case '_' :
            *etat = NOUVELLE_COMMANDE;
        break;

        default :
            *etat = ATTENTE_NVELLE_COMMANDE;
        break;
    }
}

void etat_cell(FILE* fichier, Maille* maille, int* etat, int* retour, char* c)
{
   *c = lire_lettre(fichier);
    switch (*c)
    {
        case EOF :
            *etat = FIN_FICHIER;
        break;

        case 'a' :
            traiter_sous_commande(fichier, maille, etat, retour, c, "ngle", CELL_ANGLE);
        break;

        case 'l' :
            traiter_sous_commande(fichier, maille, etat, retour, c, "ength", CELL_LENGTH);
        break;

        case '_' :
            *etat = NOUVELLE_COMMANDE;
        break;

        default :
            *etat = ATTENTE_NVELLE_COMMANDE;
        break;
    }
}

void etat_cell_length(FILE* fichier, Maille* maille, int* etat, int* retour, char* c)
{
     *c = lire_lettre(fichier);

    switch (*c)
    {
        case EOF :
            *etat = FIN_FICHIER;
        break;

        case 'a' :
            *retour = detection_reel(fichier, &(maille->a));
            if(*retour%4 <= 1)         // On n'a pas atteint l underscore
                *etat = ATTENTE_NVELLE_COMMANDE;
            else                       // On a atteint l'underscore
                *etat = NOUVELLE_COMMANDE;
            if(*retour/4 == 1)
                *etat = FIN_FICHIER;
        break;
    }
}
