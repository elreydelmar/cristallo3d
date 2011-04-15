#include "automate.h"

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

            case CELL_ANGLE:
                etat_cell_angle(fichier, maille, &etat, &retour, &c);
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

        case 'b' :
            *retour = detection_reel(fichier, &(maille->b));
            if(*retour%4 <= 1)         // On n'a pas atteint l underscore
                *etat = ATTENTE_NVELLE_COMMANDE;
            else                       // On a atteint l'underscore
                *etat = NOUVELLE_COMMANDE;
            if(*retour/4 == 1)
                *etat = FIN_FICHIER;
        break;

        case 'c' :
            *retour = detection_reel(fichier, &(maille->c));
            if(*retour%4 <= 1)         // On n'a pas atteint l underscore
                *etat = ATTENTE_NVELLE_COMMANDE;
            else                       // On a atteint l'underscore
                *etat = NOUVELLE_COMMANDE;
            if(*retour/4 == 1)
                *etat = FIN_FICHIER;
        break;

        case '_' :
            *etat = NOUVELLE_COMMANDE;
        break;

        default :
            *etat = ATTENTE_NVELLE_COMMANDE;
    }
}

void etat_cell_angle(FILE* fichier, Maille* maille, int* etat, int* retour, char* c)
{
    *c = lire_lettre(fichier);
    switch (*c)
    {
        case EOF :
            *etat = FIN_FICHIER;
        break;

        case 'a' :
            *retour = detection_mot(fichier, "lpha");
            if(*retour/4 == 1) // End of file
            {
                *etat = FIN_FICHIER;
                return;
            }

            if(*retour%4 == 0)       // Non trouve non fin de ligne : cas classique 1
                *etat = ATTENTE_NVELLE_COMMANDE;
            else if(*retour%4 == 1) // Trouve et non fin de ligne
            {
                *retour = detection_reel(fichier, &(maille->alpha));
                        if(*retour%4 <= 1)         // On n'a pas atteint l underscore
                            *etat = ATTENTE_NVELLE_COMMANDE;
                        else                       // On a atteint l'underscore
                            *etat = NOUVELLE_COMMANDE;
                        if(*retour/4 == 1)
                            *etat = FIN_FICHIER;
            }
            else                 //on a passe l underscore : bye bye
                *etat = NOUVELLE_COMMANDE;

        break;

        case 'b' :
            *retour = detection_mot(fichier, "eta");
            if(*retour/4 == 1) // End of file
            {
                *etat = FIN_FICHIER;
                return;
            }

            if(*retour%4 == 0)       // Non trouve non fin de ligne : cas classique 1
                *etat = ATTENTE_NVELLE_COMMANDE;
            else if(*retour%4 == 1) // Trouve et non fin de ligne
            {
                *retour = detection_reel(fichier, &(maille->beta));
                        if(*retour%4 <= 1)         // On n'a pas atteint l underscore
                            *etat = ATTENTE_NVELLE_COMMANDE;
                        else                       // On a atteint l'underscore
                            *etat = NOUVELLE_COMMANDE;
                        if(*retour/4 == 1)
                            *etat = FIN_FICHIER;
            }
            else                 //on a passe l underscore : bye bye
                *etat = NOUVELLE_COMMANDE;

        break;

        case 'g' :
            *retour = detection_mot(fichier, "amma");
            if(*retour/4 == 1) // End of file
            {
                *etat = FIN_FICHIER;
                return;
            }

            if(*retour%4 == 0)       // Non trouve non fin de ligne : cas classique 1
                *etat = ATTENTE_NVELLE_COMMANDE;
            else if(*retour%4 == 1) // Trouve et non fin de ligne
            {
                *retour = detection_reel(fichier, &(maille->gamma));
                        if(*retour%4 <= 1)         // On n'a pas atteint l underscore
                            *etat = ATTENTE_NVELLE_COMMANDE;
                        else                       // On a atteint l'underscore
                            *etat = NOUVELLE_COMMANDE;
                        if(*retour/4 == 1)
                            *etat = FIN_FICHIER;
            }
            else                 //on a passe l underscore : bye bye
                *etat = NOUVELLE_COMMANDE;

        break;

        case '_' :
            *etat = NOUVELLE_COMMANDE;
        break;

        default :
            *etat = ATTENTE_NVELLE_COMMANDE;
        break;
    }
}

L_ligne* automate_symmetry(FILE* fichier, int* etat, int* retour, char* c)
{
    L_ligne* lignes = NULL;
    Arbre* x = NULL;
    Arbre* y = NULL;
    Arbre* z = NULL;
    Arbre** courant = NULL;
    int coordonnee = NONE;
    int apostrophe_ouvert = 0;
    Valeur val;
    double decimale = 0.1;

    while(*etat != ATTENTE_NVELLE_COMMANDE && *etat != FIN_FICHIER)
    {
        *c = lire_lettre(fichier);
        if(*c == EOF)
            *etat = FIN_FICHIER;
        else if(*c == 'l') // de loop
            *etat = ATTENTE_NVELLE_COMMANDE;
        else if(*c == '\'')
            apostrophe_ouvert = !apostrophe_ouvert;
        else if(*c == ' ')  // on ne fait rien
        {}
        else
        {
            switch(*etat)
            {
                case s_ATT_LIGNE : // on fait pareil que OP sauf que l on vide nos arbres
                    if(x != NULL)
                    {
                        vider_arbre(x);
                        x = NULL;
                    }
                    if(y != NULL)
                    {
                        vider_arbre(y);
                        y = NULL;
                    }
                    if(z != NULL)
                    {
                        vider_arbre(z);
                        z = NULL;
                    }
                    coordonnee = NONE;

                case s_OP :
                    if(is_variable(*c))  // une variable
                    {
                        if(coordonnee == NONE)
                        {
                            coordonnee = s_X;
                            courant = &x;
                        }
                        *etat = s_VAR;
                        // On cherche l'element
                        if(*c == 88 || *c ==120)
                            val.variable = X;
                        else if(*c == 89 || *c ==121)
                            val.variable = Y;
                        else if(*c == 90 || *c ==122)
                            val.variable = Z;
                        *courant = ajouter_element(*courant, creer_element(VAR, val));
                    }
                    else if(is_chiffre(*c)) // Un chiffre
                    {
                        if(coordonnee == NONE)
                        {
                            coordonnee = s_X;
                            courant = &x;
                        }
                        *etat = s_CG;
                        val.reel = char_to_chiffre(*c);
                    }
                    else
                        *etat = s_ATT_LIGNE; // erreur, on prend la prochaine ligne
                break;

                case s_VAR :
                    if(is_operateur(*c))
                    {
                        val.operateur = char_to_op(*c);
                        *courant = ajouter_element(*courant, creer_element(OP, val));
                        *etat = s_OP;
                    }
                    else if(*c == ',')
                        *etat = s_VIRGULE;
                    else if(*c == '\n')
                        *etat = s_FINAL;
                    else
                        *etat = s_ATT_LIGNE;
                break;

                case s_CG :
                    if(is_chiffre(*c))
                    {
                        val.reel *= 10;
                        val.reel += char_to_chiffre(*c);
                    }
                    else if(*c == '.')
                        *etat = s_POINT;
                    else if(*c == ',')
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        *etat = s_VIRGULE;
                    }
                    else if(*c == '\n')
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        *etat = s_FINAL;
                    }
                    else if(is_operateur(*c))
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        val.operateur = char_to_op(*c);
                        *courant = ajouter_element(*courant, creer_element(OP, val));
                        *etat = s_OP;
                    }
                    else
                        *etat = s_ATT_LIGNE;
                break;

                case s_POINT :
                    if(is_chiffre(*c))
                    {
                        virgule = 0.1;
                        val.reel += (0.1 * char_to_chiffre(*c));
                    }
                    else if(*c == ',')
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        *etat = s_VIRGULE;
                    }
                    else if(*c == '\n')
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        *etat = s_FINAL;
                    }
                    else if(is_operateur(*c))
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        val.operateur = char_to_op(*c);
                        *courant = ajouter_element(*courant, creer_element(OP, val));
                        *etat = s_OP;
                    }
                    else
                        *etat = s_ATT_LIGNE;
                break;

                case s_CD :
                    if(is_chiffre(*c))
                    {
                        virgule *= 0.1;
                        val.reel += (virgule*char_to_chiffre(*c));
                    }
                    else if(*c == ',')
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        *etat = s_VIRGULE;
                    }
                    else if(*c == '\n')
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        *etat = s_FINAL;
                    }
                    else if(is_operateur(*c))
                    {
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        val.operateur = char_to_op(*c);
                        *courant = ajouter_element(*courant, creer_element(OP, val));
                        *etat = s_OP;
                    }
                    else
                        *etat = s_ATT_LIGNE;
                break;

            }
        }
    }

    return lignes;
}

char is_chiffre(char c)
{
    return ((char) (c >= 48 && c <= 57));
}

char is_operateur(char c)
{
    return ((char)(c == '+' || c == '-' || c == '*' || c == '/'));
}

char is_variable(char c)
{
    return ((char)(c >= 88 && c <= 90) || (c >= 120 && c <= 122));
}

Op char_to_op(char c)
{
    switch(c)
    {
        case '+' :
            return PLUS;
        case '-' :
            return MOINS;
        case '*' :
            return FOIS;
        case '/' :
            return DIVISE;
        default :   // Pas cense arriver
            return PLUS;
    }
}

double char_to_chiffre(char c)
{
    return ((double) (c-48));
}
