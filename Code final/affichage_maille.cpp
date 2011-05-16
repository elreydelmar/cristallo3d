#include "affichage_maille.h"


void test_affichage(int affiche[9], Camera* C, Octree* O)
{
    int i;
    for (i=0; i<9; i++) affiche[i]=1;

    if (prod_scal(C->z, {1,0,0})<0 & C->origine.x<O->M.position.x)
    {
        for (i=4; i<9; i++) affiche[i]=0; //annule les x positifs
    }
    if (prod_scal(C->z, {1,0,0})>0 & C->origine.x>O->M.position.x)
    {
        affiche[8]=0;
        for (i=0; i<4; i++) affiche[i]=0; //annule les x négatifs
    } //test sur x

    if (prod_scal(C->z, {0,1,0})<0 & C->origine.y<O->M.position.y)
    {
        affiche[8]=0;
        for (i=0; i<4; i++) affiche[2*i+1]=0; //annule les y positifs
    }
    if (prod_scal(C->z, {0,1,0})>0 & C->origine.y>O->M.position.y)
    {
        for (i=0; i<5; i++) affiche[2*i]=0; //annule les y négatifs
    } //test sur y

    if (prod_scal(C->z, {0,0,1})<0 & C->origine.z<O->M.position.z)
    {
        affiche[2]=0;
        affiche[3]=0;
        affiche[6]=0;
        affiche[7]=0;
        affiche[8]=0;//annule les z positifs
    }
    if (prod_scal(C->z, {0,0,1})>0 & C->origine.z>O->M.position.z)
    {
        affiche[0]=0;
        affiche[1]=0;
        affiche[4]=0;
        affiche[5]=0;
        affiche[8]=0;//annule les z négatifs
    } //test sur z
}

void afficher_atome(Atome A, Atome_Type T)
{

    Sphere sphere;
    sphere.radius=T.rayon_ionique;
    sphere.slices=100;
    sphere.stacks=100;

    Point centre;
    centre.x=A.position.x;
    centre.y=A.position.y;
    centre.z=A.position.z;

    dessiner_sphere(sphere, couleurs[T.index_couleur], centre);
}

void afficher_maille (Maille* M, Camera* C){_afficher_maille(M, C, M->atomes);}

void _afficher_maille(Maille* M, Camera* C, Octree* O)
{
    if (O==NULL) return;
    else
    {
        int affiche[9];
        test_affichage(affiche, C, O);
        if (affiche[8]==1)
        {
            Atome A=O->M;
            Atome_Type T=M->types[A.type];
            afficher_atome(A, T);
        }
        int j;
        for (j=0; j<8; j++)
        {
            if (affiche[j]==1) _afficher_maille(M, C, O->fils[j]);
        }
    }

}


/*changeme_base(double a,double b,double c,double alpha,double beta,double gamma)
{
    Point X={a,0,0};
    Point Y={b*cos(beta), b*sin(beta),0};
    Point Z={}
}*/
