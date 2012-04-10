#ifndef _ARC
#define _ARC

typedef struct ARCS {int n_arrivee; double cout; struct ARCS* arcsuiv;}*arc;
#endif


#ifndef _SOMMET
#define _SOMMET

typedef struct cellules {char* nom; int numero; struct cellules* suiv;}*sommet;
#endif


#ifndef _SOMMET_DU_CHEMIN
#define _SOMMET_DU_CHEMIN

typedef struct cellulef {int num; double cout; struct cellulef* pere;}* sommet_du_chemin;
#endif


#ifndef _SOMMET_POSSIBLE
#define _SOMMET_POSSIBLE

typedef struct SOMMET_POSSIBLES {int numerosommet; double distancedepart;}*sommetpossible;

#endif
