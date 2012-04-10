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
    L_ligne* l = NULL;

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

            case SYMMETRY :
                traiter_sous_commande(fichier, maille, &etat, &retour, &c, "equiv", EQUIV);
            break;

            case EQUIV:
                traiter_sous_commande(fichier, maille, &etat, &retour, &c, "pos", POS);
            break;

            case POS:
                traiter_sous_commande(fichier, maille, &etat, &retour, &c, "as", AS);
            break;

            case AS:
                etat_sym_equiv_pos_as(fichier, maille, &etat, &retour, &c);
            break;

            case XYZ:
                l = automate_symmetry(fichier, &etat, &retour, &c);
                afficher_l_ligne(l);
            break;

            default :
                etat = ATTENTE_NVELLE_COMMANDE;
            break;
        }

    }


    vider_l_ligne(l);

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

void etat_sym_equiv_pos_as(FILE* fichier, Maille* maille, int* etat, int* retour, char* c)
{
    *retour = detection_mot(fichier, "xyz");
    if(*retour/4 == 1) // End of file
    {
        *etat = FIN_FICHIER;
        return;
    }

    if(*retour%4 == 0)       // Non trouve non fin de ligne
        *etat = ATTENTE_NVELLE_COMMANDE;
    else if(*retour%4 == 1) // Trouve et non fin de ligne : cas classique 1
        *etat = XYZ;
    else               // on a passe l underscore
        *etat = NOUVELLE_COMMANDE;
}

L_ligne* automate_symmetry(FILE* fichier, int* etat, int* retour, char* c)
{
    *etat = s_ATT_LIGNE;

    L_ligne* lignes = NULL;
    Arbre* x = NULL;
    Arbre* y = NULL;
    Arbre* z = NULL;
    Arbre** courant = NULL;
    int coordonnee = s_X;
    int apostrophe_ouvert = 0;
    Valeur val;
    double decimale = 0.1;

    while(*etat != ATTENTE_NVELLE_COMMANDE && *etat != FIN_FICHIER)
    {
        *c = lire_lettre(fichier);
        if(*c == EOF)
            *etat = FIN_FICHIER;
        else if(*c == 'l') // de loop
        {
            if(arbre_valide(x) && arbre_valide(y) && arbre_valide(z))
            {
                lignes = add_to_l_ligne(lignes,x,y,z);
            }
            *etat = ATTENTE_NVELLE_COMMANDE;
        }
        else if(*c == '\'')
            apostrophe_ouvert = !apostrophe_ouvert;
        else if(*c == ' ')  // on ne fait rien
        {}
        else
        {
            switch(*etat)
            {

                case s_FINAL :
                    // On teste les arbres
                    if(arbre_valide(x) && arbre_valide(y) && arbre_valide(z))
                    {
                        // on ajoute a la liste
                        lignes = add_to_l_ligne(lignes,x,y,z);

                        x = NULL;
                        y = NULL;
                        z = NULL;
                    }
                // on enchaine direct sur attente ligne
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
                    coordonnee = s_X;
                    courant = &x;

                case s_OP :
                    if(is_variable(*c))  // une variable
                    {
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
                        *etat = s_CG;
                        val.reel = char_to_chiffre(*c);
                    }
                    else if(*c == '-')
                    {
                        val.reel = -1.;
                        *courant = ajouter_element(*courant, creer_element(REEL, val)); // CETTE LIGNE BUG
                        val.operateur = FOIS;
                        *courant = ajouter_element(*courant, creer_element(OP, val));
                        *etat = s_OP;
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
                        decimale = 0.1;
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
                        decimale *= 0.1;
                        val.reel += (decimale*char_to_chiffre(*c));
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

                case s_VIRGULE : // Une virgule a bon endroit a ete detectee
                    // l'element est deja ajoute
                    // on change l arbre courant
                    if(coordonnee == s_X)
                    {
                        coordonnee = s_Y;
                        courant = &y;
                    }
                    else if(coordonnee == s_Y)
                    {
                        coordonnee = s_Z;
                        courant = &z;
                    }
                    else
                        *etat = s_ATT_LIGNE;
                    if(*etat != s_ATT_LIGNE)
                    {
                        if(is_variable(*c))  // une variable
                        {
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
                        else if(*c == '-')
                        {
                            val.reel = -1.;
                            *courant = ajouter_element(*courant, creer_element(REEL, val));
                            val.operateur = FOIS;
                            *courant = ajouter_element(*courant, creer_element(OP, val));
                            *etat = s_OP;
                        }
                        else if(is_chiffre(*c)) // Un chiffre
                        {
                            *etat = s_CG;
                            val.reel = char_to_chiffre(*c);
                        }
                        else
                            *etat = s_ATT_LIGNE; // erreur, on prend la prochaine ligne
                    }
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

void afficher_l_ligne(L_ligne* l)
{
    while(l != NULL)
    {
        afficher_arbre(l->x); printf(", ");
        afficher_arbre(l->y); printf(", ");
        afficher_arbre(l->z); printf("\n");

        l = l->queue;
    }
}

void afficher_arbre(Arbre* a)
{
    if(a == NULL)
        return;

    switch(a->type)
    {
        case VAR :
            switch(a->valeur.variable)
            {
                case X : printf("x");  break;
                case Y : printf("y");  break;
                case Z : printf("z");  break;
            }
        break;

        case OP:
            printf("(");
            afficher_arbre(a->fils_g);
            switch(a->valeur.operateur)
            {
                case PLUS : printf("+");  break;
                case MOINS : printf("-");  break;
                case FOIS : printf("*");  break;
                case DIVISE : printf("/");  break;
            }
            afficher_arbre(a->fils_d);
            printf(")");
        break;

        case REEL :
            printf("%lf", a->valeur.reel);
        break;
    }
}
