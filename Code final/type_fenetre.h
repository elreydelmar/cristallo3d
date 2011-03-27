#ifndef TYPE_FENETRE_H_INCLUDED
#define TYPE_FENETRE_H_INCLUDED

// Structure qui contient toutes les infos de la fenetre
typedef struct Fenetre Fenetre;
struct Fenetre
{
    HINSTANCE instance;
    MSG message;

    HWND fenetre;
        HWND gl;
        HWND menu;

    // OpenGL
    HDC dc;
    HGLRC rc;

    // Les groupebox
    HWND cam;
    HWND maille;

    // Les boutons
    // Camera
    HWND freefly;
    HWND trackball;
    HWND anaglyphe;
    HWND c_retro;
        HWND retro;
        HWND s_retro;
        HWND t_retro;

    HWND c_distance;
        HWND s_distance;
        HWND t_distance;
        HWND ordi;
        HWND salle;
        HWND amphi;

    // Maille
    HWND adresse;
    HWND parcourir;
    HWND generer_maille;

    HWND nb_x;
    HWND nb_y;
    HWND nb_z;
    HWND s_taille;
    HWND s_espace_atome;

    HWND defaut;
    HWND aide;
};


#endif // TYPE_FENETRE_H_INCLUDED
