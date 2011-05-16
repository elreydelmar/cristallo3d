#include <math.h>

test_affichage(int affiche[9], Camera* C, Octree* O)
{
    if (prod_scal(Camera.z, {1,0,0})<0 & Camera.origine.x<Octree.M.position.x)
    {
        int i;
        for (i=4; i<9; i++) affiche[i]=0; //annule les x positifs
    }
    if (prod_scal(Camera.z, {1,0,0})>0 & Camera.origine.x>Octree.M.position.x)
    {
        affiche[8]=0;
        int i;
        for (i=0; i<4; i++) affiche[i]=0; //annule les x négatifs
    } //test sur x

    if (prod_scal(Camera.z, {0,1,0})<0 & Camera.origine.y<Octree.M.position.y)
    {
        int i;
        for (i=0; i<5; i++) affiche[2i]=0; //annule les y positifs
    }
    if (prod_scal(Camera.z, {0,1,0})>0 & Camera.origine.y>Octree.M.position.y)
    {
        affiche[8]=0;
        int i;
        for (i=0; i<4; i++) affiche[2i+1]=0; //annule les y négatifs
    } //test sur y

    if (prod_scal(Camera.z, {0,0,1})<0 & Camera.origine.z<Octree.M.position.z)
    {
        affiche[2]=0;
        affiche[3]=0;
        affiche[6]=0;
        affiche[7]=0;
        affiche[8]=0;//annule les z positifs
    }
    if (prod_scal(Camera.z, {0,0,1})>0 & Camera.origine.z>Octree.M.position.z)
    {
        affiche[0]=0;
        affiche[1]=0;
        affiche[4]=0;
        affiche[5]=0;
        affiche[8]=0;//annule les z négatifs
    } //test sur z
}

afficher_maille(Maille* M, Camera* C, Octree* O) // O est le premier sommet
{
    if (O==NULL) return;
    glPushMatrix();

    glColor3ub(couleur.r,couleur.v,couleur.b);

    int affiche[9];
    int i;
    for (i=0; i<9; i++) affiche[i]=1
    test_affichage(affiche[9], &C, &O);
    if (affiche[8]==1)
    {
        afficher_maille(&M, &C, &O)
        int j;
        for (j=0; j<8; j++)
        {
            if (affiche[i]==1) afficher_maille(&M, &C, &(O->Fils[i]))
        }
    }

    dessiner_sphere()

    int i;
    for (i=0; i<8; i++)
    {
        if (devant_camera)
        afficher_maille(O->Fils[i])
    }
    afficher_maille(O->Fils[i])

    glEnd();
    glPopMatrix();
}
