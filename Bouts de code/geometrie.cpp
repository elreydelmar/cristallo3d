#include "geometrie.h"

// Fonctions de test
void afficher_point(Point point)
{
    printf("Point (%lf, %lf, %lf)\n",point.x, point.y, point.z);
}

void afficher_ligne(Ligne l)
{
    printf ("l: (%lf,%lf,%lf),(%lf,%lf,%lf)\n", l.P.x, l.P.y, l.P.z, l.Q.x, l.Q.y, l.Q.z);
}

void afficher_matrice(Matrice4 M)
{
    int i;
    int j;
    for (i=0; i<4; i++)
    {
        for (j=0; j<4; j++)
            printf ("%lf ",M.m[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Fonctions des matrices
void set_null(Matrice4* M)
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            M->m[i][j] = 0.;
    }
}

void set_id(Matrice4* M)
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            M->m[i][j] = (i == j) ? 1. : 0.;
    }
}

void copie_matrice(Matrice4* M, Matrice4 acopier)
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            M->m[i][j] = acopier.m[i][j];
    }
}

void add_mat(Matrice4 M, Matrice4 N, Matrice4* reponse)
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            reponse->m[i][j] = M.m[i][j] + N.m[i][j];
    }
}

void sub_mat(Matrice4 M, Matrice4 N, Matrice4* reponse)
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            reponse->m[i][j] = M.m[i][j] - N.m[i][j];
    }
}

void mult_mat(Matrice4 Ml, Matrice4 Nl, Matrice4* reponse)
{
    Matrice M,N;
    int i,j;
    copie_matrice(&M,Ml);
    copie_matrice(&N,Nl);
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            reponse->m[i][j] = M.m[i][0]*N.m[0][j] + M.m[i][1]*N.m[1][j] +  M.m[i][2]*N.m[2][j] + M.m[i][3]*N.m[3][j];
        }
    }
}

void scalaire(double alpha, Matrice4 Ml, Matrice4* reponse)
{
    Matrice M;
    copie_matrice(&M,Ml);
    int i;
    int j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            reponse->m[i][j] = alpha*M.m[i][j];
        }
    }
}

double det(Matrice4 M)
{
    double determinant = 0;
    double d[4];
    d[0] = M.m[1][1]*M.m[2][2]*M.m[3][3]+M.m[1][2]*M.m[2][3]*M.m[3][1]+M.m[1][3]*M.m[2][1]*M.m[3][2]-M.m[3][1]*M.m[2][2]*M.m[1][3]-M.m[3][2]*M.m[2][3]*M.m[1][1]-M.m[3][3]*M.m[2][1]*M.m[1][2];
    d[1] = M.m[0][1]*M.m[2][2]*M.m[3][3]+M.m[0][2]*M.m[2][3]*M.m[3][1]+M.m[0][3]*M.m[2][1]*M.m[3][2]-M.m[3][1]*M.m[2][2]*M.m[0][3]-M.m[3][2]*M.m[2][3]*M.m[0][1]-M.m[3][3]*M.m[2][1]*M.m[0][2];
    d[2] = M.m[0][1]*M.m[1][2]*M.m[3][3]+M.m[0][2]*M.m[1][3]*M.m[3][1]+M.m[0][3]*M.m[1][1]*M.m[3][2]-M.m[3][1]*M.m[1][2]*M.m[0][3]-M.m[3][2]*M.m[1][3]*M.m[0][1]-M.m[3][3]*M.m[1][1]*M.m[0][2];
    d[3] = M.m[0][1]*M.m[1][2]*M.m[2][3]+M.m[0][2]*M.m[1][3]*M.m[2][1]+M.m[0][3]*M.m[1][1]*M.m[2][2]-M.m[2][1]*M.m[1][2]*M.m[0][3]-M.m[2][2]*M.m[1][3]*M.m[0][1]-M.m[2][3]*M.m[1][1]*M.m[0][2];
    int i;
    int j=1;
    for(i=0; i<4; i++)
    {
        determinant += j*M.m[i][0]*d[i];
        j=-j;
    }
    return determinant;
}

double cofacteur(Matrice4 M, int i, int j)
{
    // Calcul de la matrice auxiliaire
    double N[3][3];
    int i1 = 0, j1 = 0;
    int i2,j2;
    for(i2=0; i2<4; i2++)
    {
        if(i2 != i)
        {
            j1 = 0;
            for(j2=0; j2<4; j2++)
            {
                if(j2 != j)
                {
                    N[i1][j1] = M.m[i2][j2];
                    j1++;
                }
            }
            i1++;
        }
    }

    double signe = (i%2 == j%2) ? 1.0 : -1.0;

    // On calcule le derminant de la matrice N
    double determinant = 0.;
    for(i1=0; i1<3; i1++)
    {
        determinant += N[0][i1]*N[1][(i1+1)%3]*N[2][(i1+2)%3];
        determinant -= N[3][i1]*N[2][(i1+1)%3]*N[1][(i1+2)%3];
    }

    return determinant*signe;
}

void comatrice(Matrice4 Ml, Matrice4* reponse)
{
    Matrice M;
    copie_matrice(&M,Ml);
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            reponse->m[i][j] = cofacteur(M,i,j);
    }
}

void transposee(Matrice4 Ml, Matrice4* reponse)
{
    Matrice M;
    copie_matrice(&M,Ml);
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            reponse->m[i][j] = M.m[j][i];
    }
}

void inverse(Matrice4 M, Matrice4* reponse)
{
    double determinant = det(M);
    if(determinant == 0)
         set_null(reponse);
    else
    {
        comatrice(M, reponse);
        transposee(*reponse, reponse);
        scalaire(1/determinant, *reponse, reponse);
    }
}

Point add_pts (Point P, Point Q)
{
    Point R;
    R.x=P.x+Q.x;
    R.y=P.y+Q.y;
    R.z=P.z+Q.z;
    return R;
}

Point sub_pts (Point P, Point Q)
{
    Point R;
    R.x=P.x-Q.x;
    R.y=P.y-Q.y;
    R.z=P.z-Q.z;
    return R;
}

Point mult_scal_pts (double k, Point P)
{
    Point Q;
    Q.x=k*P.x;
    Q.y=k*P.y;
    Q.z=k*P.z;
    return Q;
}

double prod_scal (Point P, Point Q)
{
    double s;
    s=P.x*Q.x+P.y*Q.y+P.z*Q.z;
    return s;
}

Point prod_vect (Point P, Point Q)
{
    Point R;
    R.x=P.y*Q.z-P.z*Q.y;
    R.y=P.z*Q.x-P.x*Q.z;
    R.z=P.x*Q.y-P.y*Q.x;
    return R;
}

double norme (Point P)
{
    double n=sqrt(prod_scal (P,P));
    return n;
}

void normer (Point* P)
{
    *P = mult_scal_pts (1/norme(*P),*P);
}

Point mult_mat_point (Matrice4 M, Point P)
{
    Point retour;
    retour.x = M.m[0][0]*P.x + M.m[0][1]*P.y +  M.m[0][2]*P.z + M.m[0][3]*1;
    retour.y = M.m[1][0]*P.x + M.m[1][1]*P.y +  M.m[1][2]*P.z + M.m[1][3]*1;
    retour.z = M.m[2][0]*P.x + M.m[2][1]*P.y +  M.m[2][2]*P.z + M.m[2][3]*1;

    return retour;
}
