#include "GLbasic.h"

void InitGL()
{
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur
    glEnable(GL_LIGHTING); 	// Active l'éclairage
    glEnable(GL_LIGHT0); 	// Allume la lumière n°1

    init_camera();
}

void closeGL()
{
    close_camera();
}

void set_camera()
{
    if(camera_courante->changement_zoom == 1)
    {
        camera_courante->changement_zoom = 0;
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective(camera_courante->fovy,(double)(WIDTH-WIDTH_COLONNE)/HEIGHT,0.1,1000); // ratio a changer
    }
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    Point cible = add_pts(camera_courante->origine, camera_courante->z);
    gluLookAt(camera_courante->origine.x, camera_courante->origine.y, camera_courante->origine.z,
              cible.x , cible.y, cible.z,
              camera_courante->x.x,camera_courante->x.y,camera_courante->x.z);
}

void init_camera_de_merde()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)(WIDTH-WIDTH_COLONNE)/HEIGHT,0.1,1000);
}

void update_camera_de_merde()
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    gluLookAt(1.5,2,1,0,0,0,0,0,1);
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


void dessiner_point(Point point, Couleur couleur)
{
    glPushMatrix();
    glBegin(GL_POINTS);
    glColor3ub(couleur.r,couleur.v,couleur.b);
    glVertex3d(point.x,point.y,point.z);
    glEnd();
    glPopMatrix();
}


void changerepere(Point O, Point Z) //place le repère au point O, orienté suivant Z
{
    glTranslated(O.x,O.y,O.z);

    Point X;
    Point Y;

    if (Z.x==0&&Z.y==0)
    {
        return;
    }

    else if (Z.y==0&&Z.z==0)
    {
        X={0,1,0};
        Y={0,0,1};
        normer(&Z);
    }

    else if (Z.x==0&&Z.z==0)
    {
        X={0,0,1};
        Y={1,0,0};
        normer(&Z);
    }

    else
    {
        X={1,0,0};
        X=sub_pts(X,proj(X,Z));
        Y={0,1,0};
        Y=sub_pts(sub_pts(Y,proj(Y,Z)),proj(Y,X));
        normer(&X);
        normer(&Y);
        normer(&Z);
    }

    Matrice Passage;
    set_null(&Passage);
    Passage.m[0][0]=X.x;
    Passage.m[1][0]=X.y;
    Passage.m[2][0]=X.z;
    Passage.m[0][1]=Y.x;
    Passage.m[1][1]=Y.y;
    Passage.m[2][1]=Y.z;
    Passage.m[0][2]=Z.x;
    Passage.m[1][2]=Z.y;
    Passage.m[2][2]=Z.z;
    Passage.m[3][3]=1;

    GLdouble Pass[16];
    int i;
    for (i=0; i<16; i++) Pass[i]=Passage.m[i%4][i/4];

    glMultMatrixd( Pass );
}

void dessiner_ligne(Couleur couleur, Ligne ligne, double rayon) // dessine la ligne. Si rayon!=0, on met a la place de la ligne un cylindre de rayon rayon
{
    glPushMatrix();
    if (rayon==0)
    {
        glBegin(GL_LINES);
        glColor3ub(couleur.r,couleur.v,couleur.b);
        glVertex3d(ligne.P.x,ligne.P.y,ligne.P.z);
        glVertex3d(ligne.Q.x,ligne.Q.y,ligne.Q.z);
        glEnd();
    }
    else
    {
        Point Z=sub_pts (ligne.Q,ligne.P);
        changerepere (ligne.P,Z);
        dessiner_cylindre({rayon,rayon,norme(Z),8},couleur);
    }
    glPopMatrix();
}


void dessiner_cube(double arete, Couleur couleur, unsigned int echelle,double rayon) //rayon = rayon des cylindres qui forment les lignes
{
        dessiner_ligne(couleur,{{arete/2,arete/2,arete/2},{-arete/2,arete/2,arete/2}},rayon);
        dessiner_ligne(couleur,{{-arete/2,arete/2,arete/2},{-arete/2,-arete/2,arete/2}},rayon);
        dessiner_ligne(couleur,{{-arete/2,-arete/2,arete/2},{arete/2,-arete/2,arete/2}},rayon);
        dessiner_ligne(couleur,{{arete/2,-arete/2,arete/2},{arete/2,arete/2,arete/2}},rayon);
        dessiner_ligne(couleur,{{arete/2,arete/2,-arete/2},{arete/2,arete/2,arete/2}},rayon);
        dessiner_ligne(couleur,{{-arete/2,arete/2,-arete/2},{-arete/2,arete/2,arete/2}},rayon);
        dessiner_ligne(couleur,{{-arete/2,-arete/2,-arete/2},{-arete/2,-arete/2,arete/2}},rayon);
        dessiner_ligne(couleur,{{arete/2,-arete/2,-arete/2},{arete/2,-arete/2,arete/2}},rayon);
        dessiner_ligne(couleur,{{arete/2,arete/2,-arete/2},{-arete/2,arete/2,-arete/2}},rayon);
        dessiner_ligne(couleur,{{-arete/2,arete/2,-arete/2},{-arete/2,-arete/2,-arete/2}},rayon);
        dessiner_ligne(couleur,{{-arete/2,-arete/2,-arete/2},{arete/2,-arete/2,-arete/2}},rayon);
        dessiner_ligne(couleur,{{arete/2,-arete/2,-arete/2},{arete/2,arete/2,-arete/2}},rayon);
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

void sample3d()
{
    dessiner_cube(0.5, {0,0,250}, 1, 0.01);
    dessiner_sphere({0.1,100,100},{250,0,0}, {0,0,0});
    dessiner_sphere({0.1,100,100},{250,0,0}, {0.25,0.25,0.25});
    dessiner_sphere({0.1,100,100},{250,0,0}, {-0.25,0.25,0.25});
    dessiner_sphere({0.1,100,100},{250,0,0}, {0.25,-0.25,0.25});
    dessiner_sphere({0.1,100,100},{250,0,0}, {0.25,0.25,-0.25});
    dessiner_sphere({0.1,100,100},{250,0,0}, {-0.25,-0.25,0.25});
    dessiner_sphere({0.1,100,100},{250,0,0}, {0.25,-0.25,-0.25});
    dessiner_sphere({0.1,100,100},{250,0,0}, {-0.25,0.25,-0.25});
    dessiner_sphere({0.1,100,100},{250,0,0}, {-0.25,-0.25,-0.25});
    dessiner_ligne({0,0,250},{{0,0,0},{0.25,0.25,0.25}},0.01);
    dessiner_ligne({0,0,250},{{0,0,0},{-0.25,0.25,0.25}},0.01);
    dessiner_ligne({0,0,250},{{0,0,0},{0.25,-0.25,0.25}},0.01);
    dessiner_ligne({0,0,250},{{0,0,0},{0.25,0.25,-0.25}},0.01);
    dessiner_ligne({0,0,250},{{0,0,0},{-0.25,-0.25,0.25}},0.01);
    dessiner_ligne({0,0,250},{{0,0,0},{0.25,-0.25,-0.25}},0.01);
    dessiner_ligne({0,0,250},{{0,0,0},{-0.25,0.25,-0.25}},0.01);
    dessiner_ligne({0,0,250},{{0,0,0},{-0.25,-0.25,-0.25}},0.01);
}

void afficher_dessin()
{
    glFlush();
}
