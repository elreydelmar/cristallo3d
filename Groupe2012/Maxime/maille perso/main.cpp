#include <windows.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

#define Y_CHAR 15
#define ID_NB_A 2
#define ID_NB_B 3
#define ID_NB_C 4
#define ID_NB_ALPHA 5
#define ID_NB_BETA 6
#define ID_NB_GAMMA 7
#define PM 110
#define ENTETE 0
#define ID_NOMFICHIER 8
#define ID_NOMAUTEUR 9
#define ATOME 183
#define ID_NOMATOME 10
#define ID_SYM 15
#define SYM 275
#define ID_PC 11
#define PC 367
#define ID_ENREG 12
#define OTHER 449
#define ID_AIDE 13
#define ID_NOMMAILE 14
#define ID_NOMSG 16
HINSTANCE instance;

LRESULT CALLBACK procedureFenetrePrincipale(HWND, UINT, WPARAM, LPARAM);

int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,
LPSTR lignesDeCommande, int modeDAffichage)
{
    HWND fenetrePrincipale;
    MSG message;
    WNDCLASS classeFenetre;

    instance = cetteInstance;

    classeFenetre.style = 0;
    classeFenetre.lpfnWndProc = procedureFenetrePrincipale;
    classeFenetre.cbClsExtra = 0;
    classeFenetre.cbWndExtra = 0;
    classeFenetre.hInstance = NULL;
    classeFenetre.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    classeFenetre.hCursor = LoadCursor(NULL, IDC_ARROW);
    classeFenetre.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    classeFenetre.lpszMenuName =  NULL;
    classeFenetre.lpszClassName = "classeF";

    // On prévoit quand même le cas où ça échoue
    if(!RegisterClass(&classeFenetre)) return FALSE;

    fenetrePrincipale = CreateWindow("classeF", "Création personnelle de fichier .cif", WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT, 500, 558,
                                                   NULL, NULL, cetteInstance, NULL);
    if (!fenetrePrincipale) return FALSE;

    ShowWindow(fenetrePrincipale, modeDAffichage);
    UpdateWindow(fenetrePrincipale);


    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return message.wParam;
}

LRESULT CALLBACK procedureFenetrePrincipale(HWND fenetrePrincipale, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND boutons[20] = {NULL};

    switch (message)
    {
        case WM_CREATE:

               CreateWindow("STATIC", "a :", WS_CHILD | WS_VISIBLE, 15,PM+25, 30, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "b :", WS_CHILD | WS_VISIBLE, 155,PM+25, 30, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "c :", WS_CHILD | WS_VISIBLE, 305,PM+25, 30, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "alpha :", WS_CHILD | WS_VISIBLE, 15,PM+45, 80, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "béta :", WS_CHILD | WS_VISIBLE, 155,PM+45, 80, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "gamma :", WS_CHILD | WS_VISIBLE, 305,PM+45, 80, Y_CHAR+5, fenetrePrincipale, NULL, instance, NULL);
                boutons[0] = CreateWindow("BUTTON", "Parametres de Maille", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,PM+5, 475,Y_CHAR*4.5, fenetrePrincipale, NULL, instance, NULL);
                boutons[1] = CreateWindow("EDIT", "5.4533", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_AUTOHSCROLL,35,PM+25, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_A, instance, NULL);
                boutons[2] = CreateWindow("EDIT", "5.4533", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_AUTOHSCROLL,185,PM+25, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_B, instance, NULL);
                boutons[3] = CreateWindow("EDIT", "5.4533", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_AUTOHSCROLL,335,PM+25, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_C, instance, NULL);
                boutons[4] = CreateWindow("EDIT", "90", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,65,PM+45, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_ALPHA, instance, NULL);
                boutons[5] = CreateWindow("EDIT", "90", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,215,PM+45, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_BETA, instance, NULL);
                boutons[6] = CreateWindow("EDIT", "90", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,375,PM+45, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_GAMMA, instance, NULL);


                boutons[7] = CreateWindow("BUTTON", "Entête", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,ENTETE+5, 475,Y_CHAR*7, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "Nom du fichier        :", WS_CHILD | WS_VISIBLE, 15,ENTETE+45, 130, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "Nom de l'auteur      :", WS_CHILD | WS_VISIBLE, 15,ENTETE+25, 135, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "Formule Chimique  :", WS_CHILD | WS_VISIBLE, 15,ENTETE+65, 130, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "Groupe d'espace    :", WS_CHILD | WS_VISIBLE, 15,ENTETE+85, 130, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
                boutons[8] = CreateWindow("EDIT", "NaCl.cif", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,185,ENTETE+45, 100, Y_CHAR, fenetrePrincipale, (HMENU)ID_NOMFICHIER, instance, NULL);
                boutons[9] = CreateWindow("EDIT", "M. Dupont", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,185,ENTETE+25, 100, Y_CHAR, fenetrePrincipale, (HMENU)ID_NOMAUTEUR, instance, NULL);
                boutons[10] = CreateWindow("EDIT", "Na Cl", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,185,ENTETE+65, 100, Y_CHAR, fenetrePrincipale, (HMENU)ID_NOMMAILE, instance, NULL);
                boutons[19] = CreateWindow("EDIT", "F m -3 m", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,185,ENTETE+85, 100, Y_CHAR, fenetrePrincipale, (HMENU)ID_NOMSG, instance, NULL);

                boutons[11] = CreateWindow("BUTTON", "Atomes", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,ATOME+5, 475,Y_CHAR*5.8, fenetrePrincipale, NULL, instance, NULL);
                boutons[12] = CreateWindow("EDIT", "Na 0.00000 0.00000 0.00000\r\nCl 0.50000 0.50000 0.50000", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE| WS_VSCROLL | ES_AUTOVSCROLL,10,ATOME+25, 462, Y_CHAR*4, fenetrePrincipale, (HMENU)ID_NOMATOME, instance, NULL);

                boutons[13] = CreateWindow("BUTTON", "Symétries", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,SYM+5, 475,Y_CHAR*5.8, fenetrePrincipale, NULL, instance, NULL);
                boutons[14] = CreateWindow("EDIT", "x,y,z", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE| WS_VSCROLL | ES_AUTOVSCROLL,10,SYM+25, 462, Y_CHAR*4, fenetrePrincipale, (HMENU)ID_SYM, instance, NULL);

                //boutons[15] = CreateWindow("BUTTON", "Paramètres supplémentaires (Optionnel)", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,PC+5, 475,Y_CHAR*5.8, fenetrePrincipale, NULL, instance, NULL);
                //boutons[16] = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE| WS_VSCROLL|ES_AUTOVSCROLL,10,PC+25, 462, Y_CHAR*4, fenetrePrincipale, (HMENU)ID_PC, instance, NULL);
                boutons[17] = CreateWindow("BUTTON", "Enregistrer", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,5,OTHER+25, 233, Y_CHAR*2, fenetrePrincipale, (HMENU)ID_ENREG, instance, NULL);
                boutons[18] = CreateWindow("BUTTON", "Aide", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,5+240,OTHER+25, 233, Y_CHAR*2, fenetrePrincipale, (HMENU)ID_AIDE, instance, NULL);
return 0;

        case WM_COMMAND:




            switch(LOWORD(wParam))
            {
                case ID_NOMFICHIER:
                break;
                case ID_NOMAUTEUR:


                    break;
                case ID_NOMMAILE:

                    break;
                case ID_NB_A:

                    break;
                case ID_NB_B:

                    break;
                case ID_NB_C:

                    break;
                case ID_NB_ALPHA:

                    break;
                case ID_NB_BETA:

                    break;
                case ID_NB_GAMMA:

                    break;
                case ID_NOMATOME:

                    break;
                case ID_SYM:

                    break;
                case ID_PC:

                    break;
                case ID_ENREG:
                // LA QUIL FAUT METTRE
{

                TCHAR buf[1000]={"Mailles Personnelles\\"};
                TCHAR buf1[300];
                UINT GetDlgItemText (HWND hDlg,int nIDDlgItem,LPTSTR lpString,int nMaxCount); //initialisation
                UINT freefps;
                freefps=GetDlgItemText(fenetrePrincipale, ID_NOMFICHIER, buf1, 250);
                strcat(buf, buf1);
                FILE * fichier = fopen(buf,"w");
                if(fichier == NULL) // Test ouverture canal
                {
                    MessageBox(NULL,"Erreur Fichier","Enregistrement",MB_OK);
                }


                //FILE * fichier = fopen("test.cif","w"); //on ouvre/crée le fichier en ecriture
                // on crée un buffer qui recoit le texte de l'edit box

                //AUTEUR

                freefps=GetDlgItemText(fenetrePrincipale, ID_NOMAUTEUR, buf, 256); // on affecte au buffer le texte de l'edit box du bouton
                fprintf(fichier, "# Fichier maille personnelle créé à partir du logiciel cristallo 3D\n# GRENOBLE INP PHELMA\n#####################################################################\n\r\n");
                fprintf(fichier, "loop_\n");
                fprintf(fichier, "_publ_author_name\t\t\n'%s'\r\n",buf);


                //FORMULE CHIM
                freefps=GetDlgItemText(fenetrePrincipale, ID_NOMMAILE, buf, 256);
                fprintf(fichier, "_chemical_formula_sum\t\t'%s'\r\n",buf);
                freefps=GetDlgItemText(fenetrePrincipale, ID_NOMSG, buf, 256);
                fprintf(fichier, "_symmetry_space_group_name_H-M\t\t'%s'\r\n",buf);
                //A
                double fps_a;
                freefps=GetDlgItemText(fenetrePrincipale, ID_NB_A, buf, 7);
                fps_a=strtod(buf, NULL);
                fprintf(fichier, "_cell_length_a\t\t\t%.4f\r\n",fps_a);
                //B
                double fps_b;
                freefps=GetDlgItemText(fenetrePrincipale, ID_NB_B, buf, 7);
                fps_b=strtod(buf, NULL);
                fprintf(fichier, "_cell_length_b\t\t\t%.4f\r\n",fps_b);
                //C
                double fps_c;
                freefps=GetDlgItemText(fenetrePrincipale, ID_NB_C, buf, 7);
                fps_c=strtod(buf, NULL);
                fprintf(fichier, "_cell_length_c\t\t\t%.4f\r\n",fps_c);
                //Alpha
                double fps_alpha;
                freefps=GetDlgItemText(fenetrePrincipale, ID_NB_ALPHA, buf, 7);
                fps_alpha=strtod(buf, NULL);
                fprintf(fichier, "_cell_angle_alpha\t\t%.4f\r\n",fps_alpha);
                //Beta
                double fps_beta;
                freefps=GetDlgItemText(fenetrePrincipale, ID_NB_BETA, buf, 7);
                fps_beta=strtod(buf, NULL);
                fprintf(fichier, "_cell_angle_beta\t\t\t%.4f\r\n",fps_beta);
                //Gamma
                double fps_gamma;
                freefps=GetDlgItemText(fenetrePrincipale, ID_NB_GAMMA, buf, 7);
                fps_gamma=strtod(buf, NULL);
                fprintf(fichier, "_cell_angle_gamma\t\t%.4f\r\n",fps_gamma);
                fprintf(fichier, "loop_\n");
                fprintf(fichier, "_symmetry_equiv_pos_as_xyz\n");
                //Symetries
                freefps=GetDlgItemText(fenetrePrincipale, ID_SYM, buf, 1001);
                fprintf(fichier, "%s\r\n",buf);
                fprintf(fichier, "loop_\n_atom_site_label\n_atom_site_fract_x\n_atom_site_fract_y\n_atom_site_fract_z\n_atom_site_U_iso_or_equiv\n");
                //ATOME
                freefps=GetDlgItemText(fenetrePrincipale, ID_NOMATOME, buf, 256);
                fprintf(fichier, "%s\r\n",buf);




fclose(fichier);

int REF2 = MessageBox(NULL,"fichier .cif créé\r\nVoulez-vous fermer l'éditeur ?","Enregistrement",MB_ICONINFORMATION | MB_YESNO);
if (REF2==IDYES){
PostQuitMessage(0);}


}

                    break;
                case ID_AIDE:
                    HINSTANCE err = ShellExecute(NULL,"open", "aide1.pdf",NULL, "extern2",SW_SHOWNORMAL);
                    if((int)err ==  SE_ERR_NOASSOC)
                    MessageBox(NULL, "Erreur : Adobe Reader n'est pas associé avec les fichiers pdf", "Aide",MB_OK);
                    break;


            }
            return 0;

        case WM_CLOSE:
        {


            int REF = MessageBox(NULL, "Etes-vous sûr de vouloir de quitter ?", "Quitter",MB_ICONWARNING | MB_YESNO);
            if (REF==IDYES){
            PostQuitMessage(0);

            }return 0;
            }

        default:
            return DefWindowProc(fenetrePrincipale, message, wParam, lParam);
    }
}


