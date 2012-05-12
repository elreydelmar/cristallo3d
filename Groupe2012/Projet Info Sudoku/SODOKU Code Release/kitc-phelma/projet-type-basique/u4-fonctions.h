// u4-fonctions.h
// Sentinelle d'inclusion
#ifndef _u4_fonctions_h
#define _u4_fonctions_h

// Definition des constantes
#define DUREE_CYCLE 0.015    // 0.500 secondes, depend du materiel utilise
#define RAYON_BOULE  20

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
struct Donnees //Les variables cree ici sont globales
{
    int CaseSaisieX;
    int CaseSaisieY;
    int ActuON;
    int DejaOccupe;
    int Dark;
    int Done;
    int Time;
    int Seconds;
    int Min;
    int Heu;
    int Chrono;
    int EnSaisie;
    int Incorrect;
    int Recommencer;
    int Solution;
};

// Déclaration des structures

struct grille
{
    int table[81];
} ;

// On exporte en variable globale les structures crées
extern struct grille grillin;
extern struct grille GrilleResolue;
extern struct grille GrilleTemp;


extern int PosX;
extern int PosY;

extern struct Donnees gDonnees; // On a exporté les données en variable globale

// Déclaration des sous-programmes
void InitialiserDonnees() ;
void DeplacerBouleSansRebond() ;
void DeplacerBouleAvecRebonds() ;
void CreationGrille(grille *);
void PreparationGrille(grille *, int);
int CompteurCasesOccupees(grille *);
void ResolutionGrilleLigneParLigne(grille *);
void ResolutionGrilleMrLinux(grille *);
// Utilitaires
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
