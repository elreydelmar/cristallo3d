#ifndef CAMERA_H
#define CAMERA_H

struct _Camera
{
    // Triedre camera
    Point origine; // position de la camera
    Point x;
    Point y;
    Point z; // designe aussi la direction

    Point centre; // Centre pour le Trackball, aligne avec pos et cible
    double fovy; // angle de zoom
    int changement_zoom; // booleen qui indique si il y a eu changement du fovy
};
typedef struct _Camera Camera;

// Ces 2 fonctions ne font qu'avancer la camera, un "travelling"
void avancer_camera(Camera* c, double pas); // (pas < 0 ou > 0)
void reculer_camera(Camera* c, double pas); // utilise avancer_camera

// Ces 4 fonctions font bouger l'ecran vers la gauche, droite, haut, bas, sans changer l'angle
void glisser_gauche(Camera* c, double pas);
void glisser_droite(Camera* c, double pas);
void glisser_haut(Camera* c, double pas);
void glisser_bas(Camera* c, double pas);

void zoom(Camera* c, double facteur); // change la "focale"

/*Ces 4 fonctions s utilisent avec la camera Trackball*/
void tourner_gauche(Camera* c, double pas);
void tourner_droite(Camera* c, double pas);
void tourner_haut(Camera* c, double pas);
void tourner_bas(Camera* c, double pas);

#endif
