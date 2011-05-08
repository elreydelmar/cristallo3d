#ifndef ALLOC_DEBUG_H_INCLUDED
#define ALLOC_DEBUG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Alloc Alloc;
struct Alloc
{
   void* ptr;
   Alloc* suivant;
};

//extern Alloc* g_alloc;

void ajouter_allocation(void* ptr);
void supprimer_allocation(void* ptr);
int chercher_allocation(void* ptr);

#endif // ALLOC_DEBUG_H_INCLUDED
