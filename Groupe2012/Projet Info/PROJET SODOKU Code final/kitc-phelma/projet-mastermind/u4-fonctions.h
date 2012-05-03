// u4-fonctions.h
// Sentinelle d'inclusion
#ifndef _u4_fonctions_h
#define _u4_fonctions_h

// Definition des constantes
#define DUREE_CYCLE 0.015    // 0.500 secondes, depend du materiel utilise

// Constantes pour le mastermind
#define RAYON_PION  20 // Rayon d'un pion standard
#define NB_COULEURS 6             // nombre de couleurs de pions
#define NB_MAX_COUPS 10           // le joueur doit trouver en moins de NB_MAX_COUPS
#define NB_PIONS 4                // NB_PIONS dans une combinaison (couleurs differentes)

// Declaration des donnees du projet

// Structure de definition de la boule
struct Boule
{
    int X;
    int Y;
    int VX;
    int VY;
} ;

// Structure globale pour les variables fonctionnelles
struct Donnees
{
    struct Boule    Boule ;
    int             Rebond ;
    //Definition des donnees du projet mastermind
    int Solution[NB_PIONS];        // La solution du jeu tiree au sort par le programme
    int TableauJeu[NB_MAX_COUPS][NB_PIONS];   // Le tableau des pions de toutes les lignes de jeu
    int LigneCourante;             // numero de la ligne de jeu courante entre 0 et NB_MAX_COUPS-1 inclus
    int PionCourant;               // Pion de couleur selectionne courant parmi les 6 possibles, numero de 0 a NB_COULEURS-1, utile en mode graphique uniquement
    int BienPlaces[NB_MAX_COUPS];  // le nombre de BP et MP pour chaque coup
    int MalPlaces[NB_MAX_COUPS];   // Ces tableaux ne sont pas necessaires en mode texte mais tres utiles en mode graphique
    int SentinelleSolution;        // Flag quand le bouton Solution est sollicite
    int GameOver;                  // 0 : jeu en cours, 1 : jeu fini et perdu, 2 : jeu fini et gagne
};

extern struct Donnees gDonnees;

// Déclaration des sous-programmes
void InitialiserDonnees() ;
void DeplacerBouleSansRebond() ;
void DeplacerBouleAvecRebonds() ;
// Declaration des sous-programmes exportes pour le mastermind
void initialisation();
void compteBPMP();
// utilitaires
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
