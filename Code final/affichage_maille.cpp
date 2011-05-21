#include "geometrie.h"
#include "affichage_maille.h"



Matrice passage(double a,double b,double c,double alpha,double beta,double gamma)
{
    Matrice P;
    set_id(&P);
    P.m[0][0]=a;
    P.m[0][1]=b*cos(gamma);
    P.m[1][1]=b*sin(gamma);
    P.m[0][2]=c*cos(beta);
    P.m[1][2]=c*(cos(alpha)/sin(gamma)-cos(beta)/tan(gamma));
    P.m[2][2]=c*sqrt(1-cos(beta)*cos(beta)-(cos(alpha)/sin(gamma)-cos(beta)/tan(gamma))*(cos(alpha)/sin(gamma)-cos(beta)/tan(gamma)));
    return P;
}

void afficher_atome(Atome A, Atome_Type T, Matrice P)
{

    Sphere sphere;
    sphere.radius=T.rayon_ionique;
    sphere.slices=10;
    sphere.stacks=10;

    Point centre;
    centre.x=A.position.x;
    centre.y=A.position.y;
    centre.z=A.position.z;
    centre=mult_mat_point(P, centre);

    dessiner_sphere(sphere, couleurs[T.index_couleur], centre);
}

void afficher_contour(Maille* M, Matrice P)
{
    Point C={0,0,0};
    Point X={P.m[0][0], P.m[1][0], P.m[2][0]};
    Point Y={P.m[0][1], P.m[1][1], P.m[2][1]};
    Point Z={P.m[0][2], P.m[1][2], P.m[2][2]};
    Point S1=add_pts(add_pts(X,Y),Z); //X+Y+Z
    Point S2=add_pts(sub_pts(Y,X),Z); //-X+Y+Z
    Point S3=add_pts(sub_pts(X,Y),Z); //X-Y+Z
    Point S4=sub_pts(add_pts(X,Y),Z); //X+Y-Z
    Point S5=sub_pts(sub_pts(Z,X),Y); //-X-Y+Z
    Point S6=sub_pts(sub_pts(X,Z),Y); //X-Y-Z
    Point S7=sub_pts(sub_pts(Y,X),Z); //-X+Y-Z
    Point S8=sub_pts(sub_pts(sub_pts(C,X),Y),Z); //-X-Y-Z

    dessiner_ligne({120,120,120},{S1,S2},0.01);
    dessiner_ligne({120,120,120},{S2,S5},0.01);
    dessiner_ligne({120,120,120},{S5,S3},0.01);
    dessiner_ligne({120,120,120},{S3,S1},0.01);
    dessiner_ligne({120,120,120},{S4,S1},0.01);
    dessiner_ligne({120,120,120},{S7,S2},0.01);
    dessiner_ligne({120,120,120},{S8,S5},0.01);
    dessiner_ligne({120,120,120},{S6,S3},0.01);
    dessiner_ligne({120,120,120},{S4,S7},0.01);
    dessiner_ligne({120,120,120},{S7,S8},0.01);
    dessiner_ligne({120,120,120},{S8,S6},0.01);
    dessiner_ligne({120,120,120},{S6,S4},0.01);
}

void afficher_les_atomes (Maille* M, Matrice P){_afficher_les_atomes(M, M->atomes, P);}

void _afficher_les_atomes(Maille* M, Octree* O, Matrice P)
{
    if (O==NULL) return;
    else
    {
        Atome A=O->M;
        Atome_Type T=M->types[A.type];
        afficher_atome(A, T, P);

        int j;
        for (j=0; j<8; j++) _afficher_les_atomes(M, O->fils[j], P);
    }
}

void afficher_maille(Maille* M)
{
    Matrice P=passage (M->agrandissement*M->a, M->agrandissement*M->b, M->agrandissement*M->c, M->alpha, M->beta, M->gamma);
    afficher_contour(M, P);
    afficher_les_atomes(M, P);
}

