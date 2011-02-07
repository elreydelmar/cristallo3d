#include "geometrie.h"

void afficher_point(Point point)
{
    printf("Point (%lf, %lf, %lf)\n",point.x, point.y, point.z);
}

void afficher_matrice(Matrice4 M)
{
    int i;
    int j;
    for (i=0; i<4; i++)
        {for (j=0; j<4; j++)
            printf ("Matrice (%lf)",M.m[i][j]);
        }
}
