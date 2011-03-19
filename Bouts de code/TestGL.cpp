#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "geometrie.h"
#include "TestGL.h"


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

void set_couleur(Couleur couleur)
{
    glColor3ub(couleur.r, couleur.v, couleur.b);
}

void set_point(Point p)
{
    glVertex3d(point.x,point.y,point.z);
}

void dessiner_point(Point point, Couleur couleur)
{
    glBegin(GL_POINTS);
        set_couleur(couleur);
        set_point(point);
    glEnd();
}


void dessiner_ligne/*adapter*/(Ligne ligne/*adapter*/, Couleur couleur)
{
    glPushMatrix();
    glBegin(GL_LINES/*adapter le GL*/);
        set_couleur(couleur);
        /*adapter les sommets à la figure géométrique*/
        set_point(ligne.P);
        set_point(ligne.Q);
    glEnd();
    glPopMatrix();
}
