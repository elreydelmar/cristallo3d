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
    // On initialise le generateur de nombres aleatoires
    srand(time(NULL));

    // On initialise la boule
    gDonnees.Boule.X = L_ZONE / 2 ;
    gDonnees.Boule.Y = L_ZONE / 2 ;
    gDonnees.Boule.VX = -1 ;
    gDonnees.Boule.VY = 2 ;

        // On initialise la boule
    gDonnees.Boule2.X = L_ZONE / 2 -50;
    gDonnees.Boule2.Y = L_ZONE / 2 -50;
    gDonnees.Boule2.VX = 2 ;
    gDonnees.Boule2.VY = 1 ;


    // Exemple son
    // JouerSon("media/r2d2.mp3");
}


void DeplacerBouleSansRebond()
{
    // Nouvelle position de la boule ...
    gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX ;
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY ;

    // ... ramenee sur la sphere
    if ( gDonnees.Boule.X > L_ZONE )
        gDonnees.Boule.X = gDonnees.Boule.X - L_ZONE;

    if ( gDonnees.Boule.X < 0 )
        gDonnees.Boule.X = L_ZONE + gDonnees.Boule.X ;

    if ( gDonnees.Boule.Y > H_ZONE )
        gDonnees.Boule.Y = gDonnees.Boule.Y - gDonnees.Boule.Y;

    if ( gDonnees.Boule.Y < 0 )
        gDonnees.Boule.Y = H_ZONE + gDonnees.Boule.Y ;




            // Nouvelle position de la boule ...
    gDonnees.Boule2.X = gDonnees.Boule2.X + gDonnees.Boule2.VX ;
    gDonnees.Boule2.Y = gDonnees.Boule2.Y + gDonnees.Boule2.VY ;

    // ... ramenee sur la sphere
    if ( gDonnees.Boule2.X > L_ZONE )
        gDonnees.Boule2.X = gDonnees.Boule2.X - L_ZONE;

    if ( gDonnees.Boule2.X < 0 )
        gDonnees.Boule2.X = L_ZONE + gDonnees.Boule2.X ;

    if ( gDonnees.Boule2.Y > H_ZONE )
        gDonnees.Boule2.Y = gDonnees.Boule2.Y - gDonnees.Boule2.Y;

    if ( gDonnees.Boule2.Y < 0 )
        gDonnees.Boule2.Y = H_ZONE + gDonnees.Boule2.Y ;
}


void DeplacerBouleAvecRebond()
{
    // Nouvelle position de la boule ...
    gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX ;
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY ;

    // ... ramenee sur la sphere
    if ( gDonnees.Boule.X > L_ZONE - RAYON_BOULE )
    {
        //gDonnees.Boule.X = gDonnees.Boule.X - L_ZONE;
        gDonnees.Boule.VX = - gDonnees.Boule.VX;
    }


    if ( gDonnees.Boule.X < RAYON_BOULE)
    {
        gDonnees.Boule.VX = - gDonnees.Boule.VX;
        //gDonnees.Boule.X = L_ZONE + gDonnees.Boule.X ;
    }

    if ( gDonnees.Boule.Y > H_ZONE-RAYON_BOULE)
        gDonnees.Boule.VY = - gDonnees.Boule.VY;

        //gDonnees.Boule.Y = gDonnees.Boule.Y - gDonnees.Boule.Y;

    if ( gDonnees.Boule.Y < RAYON_BOULE)
        gDonnees.Boule.VY = - gDonnees.Boule.VY;

        //gDonnees.Boule.Y = H_ZONE + gDonnees.Boule.Y ;



            // Nouvelle position de la boule ...
    gDonnees.Boule2.X = gDonnees.Boule2.X + gDonnees.Boule2.VX ;
    gDonnees.Boule2.Y = gDonnees.Boule2.Y + gDonnees.Boule2.VY ;

    // ... ramenee sur la sphere
    if ( gDonnees.Boule2.X > L_ZONE - RAYON_BOULE )
    {
        //gDonnees.Boule.X = gDonnees.Boule.X - L_ZONE;
        gDonnees.Boule2.VX = - gDonnees.Boule2.VX;
    }


    if ( gDonnees.Boule2.X < RAYON_BOULE)
    {
        gDonnees.Boule2.VX = - gDonnees.Boule2.VX;
        //gDonnees.Boule.X = L_ZONE + gDonnees.Boule.X ;
    }

    if ( gDonnees.Boule2.Y > H_ZONE-RAYON_BOULE)
        gDonnees.Boule2.VY = - gDonnees.Boule2.VY;

        //gDonnees.Boule.Y = gDonnees.Boule.Y - gDonnees.Boule.Y;

    if ( gDonnees.Boule2.Y < RAYON_BOULE)
        gDonnees.Boule2.VY = - gDonnees.Boule2.VY;

        //gDonnees.Boule.Y = H_ZONE + gDonnees.Boule.Y ;
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
