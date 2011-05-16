#include "fichier.h"

int charger_maille(char* nom_du_fichier, Premaille* premaille)
{
    FILE* fichier = fopen(nom_du_fichier, "r");
    if(fichier == NULL)
        return ERR_FILE_NOT_FOUND;


    init_premaille(premaille);
    char ligne[LONGUEUR_LIGNE_MAX];
    int type_ligne = NON_DEFINI;
    int in_loop = 0;
    L_int* types = NULL;

    while(fgets(ligne, LONGUEUR_LIGNE_MAX, fichier) != NULL) // le \n est present
    {
        // Etape 1 : Identification du type de ligne DONE
        type_ligne = type_de_ligne(ligne);

        // Etape 2 : Traitement selon le type
        if(type_ligne == LOOP)
        {
            vider_l_int(&types);
            in_loop = 1;
        }
        else if(type_ligne == DONNEES) // donnees
        {
            act_donnees(ligne, types, premaille);
            in_loop = 0;
        }
        else // commande
        {
            if(in_loop)
                add_l_int(&types, type_ligne);
            else
                act_uniligne(ligne, type_ligne, premaille);
        }
    }
    printf("a : %lf\n", premaille->a);
    printf("b : %lf\n", premaille->b);
    printf("c : %lf\n", premaille->c);
    printf("alpha : %lf\n", premaille->alpha);
    printf("beta : %lf\n", premaille->beta);
    printf("gamma : %lf\n", premaille->gamma);

    afficher_l_ligne(premaille->lignes);

    vider_l_int(&types);
    fclose(fichier);
    return 0;
}

void init_premaille(Premaille* premaille)
{
    premaille->lignes = NULL;
    premaille->atomes = NULL;
}

void supp_premaille(Premaille premaille)
{
//    vider_l_pre_atome(premaille.atomes);
//    vider_l_ligne(premaille.lignes);
}

int type_de_ligne(char* ligne)
{
    char* suite = NULL;
    suite = strstr(ligne, "loop_");
    if(suite != NULL)
        return LOOP;

    suite = strstr(ligne, "_cell");
    if(suite != NULL)
        return type_de_ligne_cell(suite+5);

    suite = strstr(ligne, "_symmetry_equiv_pos_as_xyz");
    if(suite != NULL)
        return SYMMETRY;

    suite = strstr(ligne, "_atom_site");
    if(suite != NULL)
        return type_de_ligne_atome(suite+10);

    if(ligne[0] == '_')
        return NON_DEFINI;
    else
        return DONNEES;
}

int type_de_ligne_cell(char* ligne)
{
    char * suite = NULL;
    suite = strstr(ligne, "_angle");
    if(suite != NULL)
        return type_de_ligne_cell_angle(suite+6);

    suite = strstr(ligne, "_length");
    if(suite != NULL)
        return type_de_ligne_cell_length(suite+7);

    return NON_DEFINI;
}

int type_de_ligne_cell_angle(char* ligne)
{
    char * suite = NULL;
    suite = strstr(ligne, "_alpha");
    if(suite != NULL)
        return CAA;

    suite = strstr(ligne, "_beta");
    if(suite != NULL)
        return CAB;

    suite = strstr(ligne, "_gamma");
    if(suite != NULL)
        return CAG;

    return NON_DEFINI;
}

int type_de_ligne_cell_length(char* ligne)
{
    char * suite = NULL;
    suite = strstr(ligne, "_a");
    if(suite != NULL)
        return CLA;

    suite = strstr(ligne, "_b");
    if(suite != NULL)
        return CLB;

    suite = strstr(ligne, "_c");
    if(suite != NULL)
        return CLC;

    return NON_DEFINI;

}

int type_de_ligne_atome(char* ligne)
{
    char * suite = NULL;
    suite = strstr(ligne, "_fract_x");
    if(suite != NULL)
        return FX;

    suite = strstr(ligne, "_fract_y");
    if(suite != NULL)
        return FY;

    suite = strstr(ligne, "_fract_z");
    if(suite != NULL)
        return FZ;

    if(!strcmp(ligne, "_label\n"))
        return LABEL;

    return NON_DEFINI;
}

void act_uniligne(char* ligne, int type, Premaille* premaille)
{
    double reel = 0;
    sscanf(ligne, "%*s %lf", &reel);

    switch(type)
    {
        case CLA : premaille->a = reel; break;
        case CLB : premaille->b = reel; break;
        case CLC : premaille->c = reel; break;
        case CAA : premaille->alpha = reel; break;
        case CAB : premaille->beta = reel; break;
        case CAG : premaille->gamma = reel; break;
        default : break;
    }
}

void act_donnees(char* ligne, L_int* types, Premaille* premaille)
{
    // On convertit la liste de types en chaine de caractere pour un scanf
    char in_scanf[512] = {0};
    L_int* buff = types;
    while(buff != NULL)
    {
        if(buff->entier == SYMMETRY)
            strcat(in_scanf, "%s ");
        else if(buff->entier == FX || buff->entier == FY || buff->entier == FZ)
            strcat(in_scanf, "%lf %*3[(0-9)] ");
        else if(buff->entier == LABEL)
            strcat (in_scanf, "%s ");
        else
            strcat (in_scanf, "%*s ");
        buff = buff->suivant;
    }

    // 2 choix, symmetry ou non
    int type_de_loop = type_loop(types);
    if(type_de_loop == 1) // symmetry
    {
        char ligne_symmetry[512] = {0};
        sscanf(ligne, in_scanf, ligne_symmetry);
        act_symmetry(ligne_symmetry, premaille);
    }
    else if(type_de_loop == 2) // x,y,z
    {
        char label[10] = {0};
        double x=0, y=0, z=0;
        sscanf(ligne, in_scanf, label, &x, &y, &z);
        act_atome(label, x, y, z, premaille);
    }
}

void act_symmetry(char* ligne, Premaille* premaille)
{
    int etat = s_OP;
    int caractere = 0;

    Arbre* x = NULL;
    Arbre* y = NULL;
    Arbre* z = NULL;
    Arbre** courant = &x;
    int coordonnee = s_X;
    int apostrophe_ouvert = 0;
    Valeur val;
    double decimale = 0.1;

    int continuer = 1;

    while(continuer)
    {
        switch(etat)
        {
            case s_FIN_LIGNE : continuer = 0; break;
            case s_OP :
                if(is_variable(ligne[caractere]))  // une variable
                {
                    etat = s_VAR;
                    // On cherche l'element
                    if(ligne[caractere] == 88 || ligne[caractere] ==120)
                        val.variable = X;
                    else if(ligne[caractere] == 89 || ligne[caractere] ==121)
                        val.variable = Y;
                    else if(ligne[caractere] == 90 || ligne[caractere] ==122)
                        val.variable = Z;
                    *courant = ajouter_element(*courant, creer_element(VAR, val));
                }
                else if(is_chiffre(ligne[caractere])) // Un chiffre
                {
                    etat = s_CG;
                    val.reel = char_to_chiffre(ligne[caractere]);
                }
                else if(ligne[caractere] == '\0' || ligne[caractere] == '\n')
                    etat = s_FIN_LIGNE;
                else if(ligne[caractere] == '\'')
                    apostrophe_ouvert = !apostrophe_ouvert;
                else if(ligne[caractere] == ' ')  // on ne fait rien
                {}
                else if(ligne[caractere] == '-')
                {
                    val.reel = -1.;
                    *courant = ajouter_element(*courant, creer_element(REEL, val)); // CETTE LIGNE BUG
                    val.operateur = FOIS;
                    *courant = ajouter_element(*courant, creer_element(OP, val));
                    etat = s_OP;
                }
                else
                    etat = s_ERREUR; // erreur
            break;

            case s_VAR :
                if(is_operateur(ligne[caractere]))
                {
                    val.operateur = char_to_op(ligne[caractere]);
                    *courant = ajouter_element(*courant, creer_element(OP, val));
                    etat = s_OP;
                }
                else if(ligne[caractere] == '\0' || ligne[caractere] == '\n')
                    etat = s_FIN_LIGNE;
                else if(ligne[caractere] == '\'')
                    apostrophe_ouvert = !apostrophe_ouvert;
                else if(ligne[caractere] == ' ')  // on ne fait rien
                {}
                else if(ligne[caractere] == ',')
                    etat = s_VIRGULE;
                else
                    etat = s_ERREUR;
            break;

            case s_CG :
                if(is_chiffre(ligne[caractere]))
                {
                    val.reel *= 10;
                    val.reel += char_to_chiffre(ligne[caractere]);
                }
                else if(ligne[caractere] == '.')
                    etat = s_POINT;
                else if(ligne[caractere] == ',')
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    etat = s_VIRGULE;
                }
                else if(is_operateur(ligne[caractere]))
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    val.operateur = char_to_op(ligne[caractere]);
                    *courant = ajouter_element(*courant, creer_element(OP, val));
                    etat = s_OP;
                }
                else if(ligne[caractere] == '\0' || ligne[caractere] == '\n')
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    etat = s_FIN_LIGNE;
                }
                else if(ligne[caractere] == '\'')
                    apostrophe_ouvert = !apostrophe_ouvert;
                else if(ligne[caractere] == ' ')  // on ne fait rien
                {}
                else
                    etat = s_ERREUR;
            break;

            case s_POINT :
                if(is_chiffre(ligne[caractere]))
                {
                    decimale = 0.1;
                    val.reel += (0.1 * char_to_chiffre(ligne[caractere]));
                }
                else if(ligne[caractere] == ',')
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    etat = s_VIRGULE;
                }
                else if(ligne[caractere] == '\0' || ligne[caractere] == '\n')
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    etat = s_FIN_LIGNE;
                }
                else if(ligne[caractere] == '\'')
                    apostrophe_ouvert = !apostrophe_ouvert;
                else if(ligne[caractere] == ' ')  // on ne fait rien
                {}
                else if(is_operateur(ligne[caractere]))
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    val.operateur = char_to_op(ligne[caractere]);
                    *courant = ajouter_element(*courant, creer_element(OP, val));
                    etat = s_OP;
                }
                else
                    etat = s_ERREUR;
            break;

            case s_CD :
                if(is_chiffre(ligne[caractere]))
                {
                    decimale *= 0.1;
                    val.reel += (decimale*char_to_chiffre(ligne[caractere]));
                }
                else if(ligne[caractere] == ',')
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    etat = s_VIRGULE;
                }
                else if(is_operateur(ligne[caractere]))
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    val.operateur = char_to_op(ligne[caractere]);
                    *courant = ajouter_element(*courant, creer_element(OP, val));
                    etat = s_OP;
                }
                else if(ligne[caractere] == '\0' || ligne[caractere] == '\n')
                {
                    *courant = ajouter_element(*courant, creer_element(REEL, val));
                    etat = s_FIN_LIGNE;
                }
                else if(ligne[caractere] == '\'')
                    apostrophe_ouvert = !apostrophe_ouvert;
                else if(ligne[caractere] == ' ')  // on ne fait rien
                {}
                else
                    etat = s_ERREUR;
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
                    etat = s_ERREUR;
                if(etat != s_ERREUR)
                {
                    if(is_variable(ligne[caractere]))  // une variable
                    {
                        etat = s_VAR;
                        // On cherche l'element
                        if(ligne[caractere] == 88 || ligne[caractere] ==120)
                            val.variable = X;
                        else if(ligne[caractere] == 89 || ligne[caractere] ==121)
                            val.variable = Y;
                        else if(ligne[caractere] == 90 || ligne[caractere] ==122)
                            val.variable = Z;
                        *courant = ajouter_element(*courant, creer_element(VAR, val));
                    }
                    else if(ligne[caractere] == '-')
                    {
                        val.reel = -1.;
                        *courant = ajouter_element(*courant, creer_element(REEL, val));
                        val.operateur = FOIS;
                        *courant = ajouter_element(*courant, creer_element(OP, val));
                        etat = s_OP;
                    }
                    else if(is_chiffre(ligne[caractere])) // Un chiffre
                    {
                        etat = s_CG;
                        val.reel = char_to_chiffre(ligne[caractere]);
                    }
                    else if(ligne[caractere] == '\0' || ligne[caractere] == '\n')
                        etat = s_FIN_LIGNE;
                    else if(ligne[caractere] == '\'')
                        apostrophe_ouvert = !apostrophe_ouvert;
                    else if(ligne[caractere] == ' ')  // on ne fait rien
                    {}
                    else
                        etat = s_ERREUR; // erreur, on prend la prochaine ligne
                }
            break;
        }
        caractere++;
    }

    // On teste les arbres
    if(arbre_valide(x) && arbre_valide(y) && arbre_valide(z))
    {
        // on ajoute a la liste
        add_to_l_ligne(&(premaille->lignes),x,y,z);

        x = NULL;
        y = NULL;
        z = NULL;
    }
    else
    {
        vider_arbre(x);
        vider_arbre(y);
        vider_arbre(z);
    }
}

void act_atome(char* label, double x, double y, double z, Premaille* premaille)
{
    // ajout de l'atome
    printf("Label : %s, x : %lf, y : %lf, z : %lf\n", label, x, y, z); // A jarter
    add_to_l_pre_atome(&(premaille->atomes), label, x, y, z);
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

