#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "maille.h"
#include "fenetre.h"
#include "camera.h"
#include "fichier.h"
#include "GLbasic.h"
#include "affichage_maille.h"
#include "anaglyphe.h"
#include <string.h>
#include <time.h>
#include <windowsx.h>

#define PAS_GLISSER 0.005
#define PAS_TETE 0.005

#define CAMERA_AUTO WM_USER+10


#define NB_TOUCHES_PAR_SECONDE 30
#define NB_CLOCKS_ECART_TOUCHE CLOCKS_PER_SEC/NB_TOUCHES_PAR_SECONDE

/*
    Contient toutes les actions possibles activees par evenement
*/

// Le type de notification d'evenement
typedef struct EventStatus EventStatus;
struct EventStatus
{
    // Menu
    int choix_camera; // 0 si freefly,1 si trackball
    int anaglyphe; // booleen
    int retro; // booleen
    double dist_retro;
    double distance;
    char adresse_fichier[255];
    char nom_fichier[255];
    char couleur [255];


    Maille* maille;
    int nb_x;
    int nb_y;
    int nb_z;
    double espace_atome;
    double taille;

    // OpenGL
    int camera_active; // 1 si la camera est active
    // Clavier
    int controle; // 1 si controle active
    int camera_auto;
};

// Globales
extern Fenetre* g_fenetre;
extern EventStatus* event_status;
extern Camera* camera_courante;

// Debut et Fin
void init_event();
void end_event();


// actions par la camera
void action_change_camera(int type); // 1 si trackball, 0 si freefly
void action_change_anaglyphe(int checked); // 1 si checked, 0 sinon

void action_activer_retro(int active); // 1 si activer, 0 sinon
double conversion_slider_edit(int slider, double min, double max);
int conversion_edit_slider(double edit, int imin, int imax, double min, double max);
void double_to_chaine(double x, char chaine[]);
int nombre_de_chiffre(double x);
int est_chiffre(char c);
double chaine_to_double(char* chaine);

void action_update_edit(HWND handle);
void action_change_edit(HWND hEdit, HWND hSlider, int priorite, double min, double max, double* achanger); // 0 si le changement vient de la trackbar
void action_default_distance(double valeur);

// actions par la maille
void action_nom();
void action_parcourir();
void action_generer(); // TODO
void action_generer_personnelle();

void action_change_nb_x();
void action_change_nb_y();
void action_change_nb_z();

int get_atome_courant();
void action_change_atome();
void action_change_couleur();

double slider_to_double(int i, double min, double max);
int double_to_slider(double x, double min, double max);
void action_change_taille(); // REFAIRE EN LINEAIRE
void action_change_espace();

void action_defaut(HWND handle);
void action_aide(HWND handle);

//Enregistrer
void action_enregistrer();
void action_charger();

// Actions du clavier
void action_up();
void action_down();
void action_left();
void action_right();

void action_controle(int valeur);
void action_demarrer_camera_auto();
void action_camera_automatique();

// Actions de la souris
void changer_activation_camera();
void action_mouse_move(int x, int y);
void action_zoom(int sens); // 1 pour le zoom, 0 pour le dezoom
void action_molette(int sens); // 1 pour vers le haut, 0 sinon


// Actions de dessin
void drawscene();
void display();

#endif // ACTIONS_H_INCLUDED
