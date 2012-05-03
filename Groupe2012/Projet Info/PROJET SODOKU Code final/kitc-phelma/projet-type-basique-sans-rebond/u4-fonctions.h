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
struct Donnees
{
    struct Boule    Boule ;
};

extern struct Donnees gDonnees;

// Déclaration des sous-programmes
void InitialiserDonnees() ;
void DeplacerBouleSansRebond() ;

// Utilitaires
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
