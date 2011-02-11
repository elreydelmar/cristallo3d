#include "geometrie.h"

// Fonctions de test
void afficher_point(Point point)
{
    printf("Point (%lf, %lf, %lf)\n",point.x, point.y, point.z);
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

Matrice4 add_mat(Matrice4 M, Matrice4 N)
{
    Matrice4 retour;
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            retour.m[i][j] = M.m[i][j] + N.m[i][j];
    }
    return retour;
}

Matrice4 sub_mat(Matrice4 M, Matrice4 N)
{
    Matrice4 retour;
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            retour.m[i][j] = M.m[i][j] - N.m[i][j];
    }
    return retour;
}

Matrice4 mult_mat(Matrice4 M, Matrice4 N)
{
    Matrice4 retour;
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            retour.m[i][j] = M.m[i][0]*N.m[0][j] + M.m[i][1]*N.m[1][j] +  M.m[i][2]*N.m[2][j] + M.m[i][3]*N.m[3][j];
        }
    }
    return retour;
}

double det(Matrice4 M)
{
    double determinant = 0;
    int i;
    for(i=0; i<3; i++)
    {
        determinant += M.m[0][i]*M.m[1][(i+1)%4]*M.m[2][(i+2)%4]*M.m[3][(i+3)%4];
        determinant -= M.m[3][i]*M.m[2][(i+1)%4]*M.m[1][(i+2)%4]*M.m[0][(i+3)%4];
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

}
