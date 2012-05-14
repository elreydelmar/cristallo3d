#ifndef TYPE_LIGNE_H_INCLUDED
#define TYPE_LIGNE_H_INCLUDED

#define NON_DEFINI 0
#define LOOP 1
#define DONNEES 2 // referme un loop


// Les cell-length
#define CLA 10
#define CLB 11
#define CLC 12
// Les cell-angle
#define CAA 20
#define CAB 21
#define CAG 22


// Les commandes pre-loop
#define SYMMETRY 101
#define FX 102
#define FY 103
#define FZ 104
#define LABEL 105

// Automate
#define s_ERREUR 200
#define s_X 201 // state X
#define s_Y 202 // state Y
#define s_Z 203 // state

#define s_OP 204
#define s_CG 205
#define s_POINT 206
#define s_CD 207
#define s_VAR 208
#define s_VIRGULE 209
#define s_FIN_LIGNE 210

#endif // TYPE_LIGNE_H_INCLUDED
