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
    sphere.slices=100;
    sphere.stacks=100;

    Point centre;
    centre.x=A.position.x;
    centre.y=A.position.y;
    centre.z=A.position.z;
    centre=mult_mat_point(P, centre);

    dessiner_sphere(sphere, couleurs[T.index_couleur], centre);
}

void afficher_maille (Maille* M){_afficher_maille(M, M->atomes);}

void _afficher_maille(Maille* M, Octree* O)
{
    Matrice P=passage (M->agrandissement*M->a, M->agrandissement*M->b, M->agrandissement*M->c, M->alpha, M->beta, M->gamma);
    if (O==NULL) return;
    else
    {
        Atome A=O->M;
        Atome_Type T=M->types[A.type];
        afficher_atome(A, T, P);

        int j;
        for (j=0; j<8; j++) _afficher_maille(M, O->fils[j]);
    }
}
