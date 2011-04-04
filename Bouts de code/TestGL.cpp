#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "geometrie.h"
#include "TestGL.h"

void InitGL()
        {

            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur
            glEnable(GL_LIGHTING); 	// Active l'éclairage
            glEnable(GL_LIGHT0); 	// Allume la lumière n°1
        }


void nouveau_dessin()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void dessiner_repere(unsigned int echelle = 1)
{
    glPushMatrix();
    glScalef(echelle,echelle,echelle);
    glBegin(GL_LINES);
    glColor3ub(0,0,255);
        glVertex3i(0,0,0);
        glVertex3i(1,0,0);
    glColor3ub(0,255,0);
        glVertex3i(0,0,0);
        glVertex3i(0,1,0);
    glColor3ub(255,0,0);
        glVertex3i(0,0,0);
        glVertex3i(0,0,1);
    glEnd();
    glPopMatrix();
}


void dessiner_point(Point point, Couleur couleur, double x, double y, double z)
{
    glPushMatrix();
    glBegin(GL_POINTS);
    glTranslated(x,y,z); //à utiliser entre chaque atome/cylindre reliant les atomes
    glColor3ub(couleur.r,couleur.v,couleur.b);
    glVertex3d(point.x,point.y,point.z);
    glEnd();
    glPopMatrix();
}


void dessiner_ligne(Couleur couleur, Ligne ligne, int baton, int rayon) // dessine la ligne. Si baton vaut 1, on met a la place de la ligne un cylindre de rayon rayon
{
    glPushMatrix();
    if (baton==0)
    {
        glBegin(GL_LINES);
        glColor3ub(couleur.r,couleur.v,couleur.b);
        glVertex3d(ligne.P.x,ligne.P.y,ligne.P.z);
        glVertex3d(ligne.Q.x,ligne.Q.y,ligne.Q.z);
    }
    else
    {
        glTranslated(ligne.P.x,ligne.P.y,ligne.P.z);

    }

    glEnd();
    glPopMatrix();
}


void dessiner_cube(double arete, Couleur couleur, unsigned int echelle = 1)
{
    glPushMatrix();

    glBegin(GL_LINES);

    glColor3ub(couleur.r,couleur.v,couleur.b);

        glVertex3d(arete/2,arete/2,arete/2);
        glVertex3d(-arete/2,arete/2,arete/2);

        glVertex3d(-arete/2,arete/2,arete/2);
        glVertex3d(-arete/2,-arete/2,arete/2);

        glVertex3d(-arete/2,-arete/2,arete/2);
        glVertex3d(arete/2,-arete/2,arete/2);

        glVertex3d(arete/2,-arete/2,arete/2);
        glVertex3d(arete/2,arete/2,arete/2);


        glVertex3d(arete/2,arete/2,arete/2);
        glVertex3d(arete/2,arete/2,-arete/2);

        glVertex3d(-arete/2,arete/2,arete/2);
        glVertex3d(-arete/2,arete/2,-arete/2);

        glVertex3d(-arete/2,-arete/2,arete/2);
        glVertex3d(-arete/2,-arete/2,-arete/2);

        glVertex3d(arete/2,-arete/2,arete/2);
        glVertex3d(arete/2,-arete/2,-arete/2);


        glVertex3d(arete/2,arete/2,-arete/2);
        glVertex3d(-arete/2,arete/2,-arete/2);

        glVertex3d(-arete/2,arete/2,-arete/2);
        glVertex3d(-arete/2,-arete/2,-arete/2);

        glVertex3d(-arete/2,-arete/2,-arete/2);
        glVertex3d(arete/2,-arete/2,-arete/2);

        glVertex3d(arete/2,-arete/2,-arete/2);
        glVertex3d(arete/2,arete/2,-arete/2);

    glEnd();
    glPopMatrix();
}


void dessiner_cylindre(Cylindre cylindre, Couleur couleur)
{
    glPushMatrix();

    GLUquadric* params = gluNewQuadric();
    gluQuadricTexture(params,GL_FALSE);
    /*glBindTexture(GL_TEXTURE_2D,texture);*/
    glColor3ub(couleur.r,couleur.v,couleur.b);
    gluCylinder(params,cylindre.base,cylindre.top,cylindre.height,cylindre.slices, 1);

    gluDeleteQuadric(params);
    glPopMatrix();
}


void dessiner_sphere(Sphere sphere, Couleur couleur, Point centre)
{
    glPushMatrix();

    GLUquadric* params = gluNewQuadric();
    gluQuadricTexture(params,GL_FALSE);
    /*glBindTexture(GL_TEXTURE_2D,texture);*/
    glTranslated(centre.x,centre.y,centre.z);
    glColor3ub(couleur.r,couleur.v,couleur.b);
    gluSphere(params,sphere.radius,sphere.slices,sphere.stacks);

    gluDeleteQuadric(params);
    glPopMatrix();
}
