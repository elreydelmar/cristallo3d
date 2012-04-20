// u4-fonctions.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
#include <stdlib.h>     // exit, rand
#include <time.h>       // time
#include <string.h>     // strcpy
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
// Programmes locaux
#include "u1-interface.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;

// Initialiser
void InitialiserDonnees()
{
    // Initialisation de Rebond
    gDonnees.Rebond = 0 ;
    // On initialise la boule
    gDonnees.Boule.X = L_ZONE / 2 ;
    gDonnees.Boule.Y = L_ZONE / 2 ;
    gDonnees.Boule.VX = 5 ;
    gDonnees.Boule.VY = 3 ;

    // Initialisations pour le mastermind
    int couleurDejaTiree[NB_COULEURS];  // drapeau pour le tirage au sort
    int i, j, tirage;

    // On initialise le generateur de nombres aleatoires
    srand(time(NULL));

    gDonnees.LigneCourante = 0;                 // 1ere proposition en attente
    gDonnees.GameOver = 0;                      // 0 : jeu en cours, 1 : jeu fini et perdu, 2 : jeu fini et gagne

    for(i=0; i<NB_MAX_COUPS ; i++)
    {
        gDonnees.BienPlaces[i] = -1;            // valeur impossible tant qu'on n'a pas joue
        gDonnees.MalPlaces[i] = -1;
    }

    for(i=0; i<NB_MAX_COUPS ; i++)
        for(j=0; j<NB_PIONS; j++)
            gDonnees.TableauJeu[i][j]=-1;       // valeur impossible tant qu'on n'a pas joue = pas de couleur

    for(i=0; i<NB_COULEURS; i++)
        couleurDejaTiree[i] = 0;         // Drapeau pour savoir si une couleur est deja  sortie

    for(i=0; i<NB_PIONS; i++)           // Tirage au sort de la solution avec 4 couleurs differentes
    {
        do
            tirage = rand() % NB_COULEURS;      // on tire une couleur au sort entre 0 et NB_COULEURS-1
        while(couleurDejaTiree[tirage]!=0);      // jusqu'a  ce que l'on obtienne une couleur pas sortie

        couleurDejaTiree[tirage]=1;             // drapeau leve
        gDonnees.Solution[i]=tirage;
    }

    gDonnees.SentinelleSolution = 0 ;           // 1 si le bouton solution est clique, 0 sinon
    gDonnees.PionCourant = -1;                  // debut de jeu : aucun pion de couleur selectionne pour jouer

    // Exemple son
    // JouerSon("media/starwars.mp3");
}

// Compte des BP et MP
void compteBPMP()
{
    int j, k;
    int CopieSolution[4]; // Copie de la solution aidant pour le calcul du nombre de pions de bonne couleur mal places

    gDonnees.BienPlaces[gDonnees.LigneCourante]=0;              // 0 a priori (avant les tests)
    gDonnees.MalPlaces[gDonnees.LigneCourante]=0;

    for(j=0; j<NB_PIONS; j++)
        if (gDonnees.Solution[j]==gDonnees.TableauJeu[gDonnees.LigneCourante][j]) // Test si pion de bonne couleur bien place
            gDonnees.BienPlaces[gDonnees.LigneCourante]++;

    // Comptage des pions de bonne couleur mal places - solution prenant en compte des pions joues de meme couleur
    for (k=0;k<=3;k++) // Initialisation de la copie de la solution
        CopieSolution[k] = gDonnees.Solution[k];

    for (j=0;j<=3;j++) // Calcul du nombre de pions de bonne couleur (gMalPlaces(LigneCourante] va inclure dans ce premier temps les bien ou mal places)
        for (k=0; k<=3; k++)
        {
            if (gDonnees.TableauJeu[gDonnees.LigneCourante][j] == CopieSolution[k])
            {
                gDonnees.MalPlaces[gDonnees.LigneCourante]++;
                CopieSolution[k] = -1; // Mise a -1 (couleur impossible) pour eviter de prendre en compte plusieurs fois la meme couleur
                break; // On sort de la boucle for si la couleur a ete trouvee pour eviter de compter une couleur plusieurs fois
            }
        }

    gDonnees.MalPlaces[gDonnees.LigneCourante] = gDonnees.MalPlaces[gDonnees.LigneCourante] - gDonnees.BienPlaces[gDonnees.LigneCourante]; // Calcul final du nombre de pions de bonne couleur mal places

}


// Utilitaires

// Joue le fichier son passe en parametre, mp3, etc...
void JouerSon(char * FichierSon)
{
    // Musique de fond
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    result = FMOD_System_GetVersion(system, &version);
    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    result = FMOD_System_CreateSound(system, FichierSon, FMOD_SOFTWARE, 0, &sound);
    result = FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
}

// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds )
{
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}
