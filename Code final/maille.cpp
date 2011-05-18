#include "maille.h"

Maille* alloc_maille()
{
    Maille* m = (Maille*) malloc(sizeof(Maille));
        m->types = NULL;
        m->atomes = NULL;
        m->lignes = NULL;
        m->p_atomes = NULL;
    return m;
}

void free_maille(Maille* maille)
{
    if(maille != NULL)
    {
        // Tableaux
        free(maille->types);

        // Octree
        vider_octree(maille->atomes);

        // Listes
        vider_l_ligne(maille->lignes);
        vider_l_pre_atome(maille->p_atomes);
    }
}

int premaille_to_maille(Premaille premaille, Maille** maille)
{
    // Premaille est-il valide ? OSEF

    free_maille(*maille);
    *maille = alloc_maille();

    (*maille)->a = premaille.a;
    (*maille)->b = premaille.b;
    (*maille)->c = premaille.c;

    (*maille)->alpha = premaille.alpha;
    (*maille)->beta = premaille.beta;
    (*maille)->gamma = premaille.gamma;

    (*maille)->lignes = premaille.lignes;
    (*maille)->p_atomes = premaille.atomes;

    // Chargement des types
    char symbole[6];
    L_Symbole* l = NULL;
    L_Pre_Atome* buff = premaille.atomes;
    (*maille)->nb_type_atomes = 0;
    while(buff != NULL)
    {
        label_to_symbole(buff->label, symbole);
        (*maille)->nb_type_atomes += ajouter_symbole(&l, symbole);
        buff = buff->queue;
    }
    L_Symbole* buff2 = l;
    int i = 0;
    int index_couleur = 0;
    (*maille)->types = (Atome_Type*) malloc(sizeof(Atome_Type)*(*maille)->nb_type_atomes);
    while(buff2 != NULL && i<(*maille)->nb_type_atomes)
    {
        strcpy((*maille)->types[i].symbole, buff2->symbole);
        // RECUPERER ICI LES INFOS SUR L ATOME
        (*maille)->types[i].rayon_ionique = 0.1;
        (*maille)->types[i].index_couleur = index_couleur;
        i++;
        index_couleur += 7;
        index_couleur %= 13;
        buff2 = buff2->suivant;
    }

    vider_symbole(l);

    // OSEF
    (*maille)->couleur_trait.r = 0;
    (*maille)->couleur_trait.v = 0;
    (*maille)->couleur_trait.b = 0;

    return 0;
}

int ajouter_symbole(L_Symbole** l, const char symbole[6])
{
    if(*l == NULL)
    {
        *l = (L_Symbole*) malloc(sizeof(L_Symbole));
        strcpy((*l)->symbole, symbole);
        (*l)->suivant = NULL;
        return 1;
    }
    else if(strcmp((*l)->symbole, symbole) == 0)
        return 0;
    else
        return ajouter_symbole(&((*l)->suivant), symbole);
}

void vider_symbole(L_Symbole* l)
{
    if(l!=NULL)
    {
        vider_symbole(l->suivant);
        free(l);
    }
}

void label_to_symbole(const char label[10], char symbole[6])
{
    int i = 0;
    while(label[i] != 0 && (label[i]<= 48 || label[i]>= 57) && i<5)
    {
        symbole[i] = label[i];
        i++;
    }
    symbole[i] = 0;
}

void charger_octree(Maille* maille, int nx, int ny, int nz)
{

    L_ligne* lignes = NULL;
    L_Pre_Atome* p_atomes = maille->p_atomes;

    // On calcule le triedre
    Point t_x = {1,0,0};
    Point t_y = {0,1,0};
    Point t_z = {0,0,1};

    Atome atome;
    int erreur = 0;
    int ajout_na = 0;
    int aff = 0;

    while(p_atomes != NULL)
    {
        atome.type = find_type(maille->types, p_atomes->label, maille->nb_type_atomes);
        lignes = maille->lignes;
        while(lignes != NULL)
        {
            // On remplit la maille
            int x,y,z;
            for(x=-nx/2; x<-nx/2+nx; x++)
            {
                for(y=-ny/2; y<-ny/2+ny; y++)
                {
                    for(z=-nz/2; z<-nz/2+nz; z++)
                    {
                        atome.position = add_pts(mult_scal_pts(calcul_arbre(lignes->x, p_atomes->x, p_atomes->y, p_atomes->z, &erreur), t_x),
                                         add_pts(mult_scal_pts(calcul_arbre(lignes->y, p_atomes->x, p_atomes->y, p_atomes->z, &erreur), t_y),
                                                 mult_scal_pts(calcul_arbre(lignes->z, p_atomes->x, p_atomes->y, p_atomes->z, &erreur), t_z)));
                        ajouter_a_l_affichage((&maille->atomes) ,atome); // PB, certains atomes ne sont pas ajoutes
                    }
                }
            }
            lignes = lignes->queue;
        }
        p_atomes = p_atomes->queue;
    }
}

int find_type(Atome_Type types[], char label[10], int nb_types)
{
    int i;
    for(i=0; i<nb_types; i++)
    {
        if(strstr(label, types[i].symbole) != NULL)
            return i;
    }
    return -1;
}
