#ifndef ETATS_H_INCLUDED
#define ETATS_H_INCLUDED

#define ATTENTE_NVELLE_COMMANDE 57
#define NOUVELLE_COMMANDE 1
#define CELL 2
#define CELL_ANGLE 3
#define CELL_LENGTH 4
#define CELL_ANGLE_ALPHA 30
#define CELL_ANGLE_BETA 31
#define CELL_ANGLE_GAMMA 32
#define CELL_LENGTH_A 40
#define CELL_LENGTH_B 41
#define CELL_LENGTH_C 42
#define SYMMETRY 12
#define ATOME 22
#define EQUIV 13
#define POS 14
#define AS 15
#define XYZ 16
#define SITE 23
#define CALC 24
#define FLAG 25
#define SOUS_PROC_ARBRE 17
#define SOUS_PROC_ATOME 18
#define FIN_FICHIER 19

// Etats pour le symmetry
#define s_X 100 // state X
#define s_Y 101 // state Y
#define s_Z 102 // state Z
#define NONE 103 // state none coord

#define s_OP 104
#define s_CG 105
#define s_POINT 106
#define s_CD 107
#define s_VAR 108
#define s_VIRGULE 109 // a faire
#define s_ATT_LIGNE 110
#define s_FINAL 111 // a faire

#endif // ETATS_H_INCLUDED
