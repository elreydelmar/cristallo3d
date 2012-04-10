#include "alloc_debug.h"

Alloc* g_alloc;

void ajouter_allocation(void* ptr)
{
    if(chercher_allocation(ptr))
        printf("Erreur : Memoire deja allouee\n");
    else
    {
        Alloc* nouveau = (Alloc*) malloc(sizeof(Alloc));
        nouveau->ptr = ptr;
        nouveau->suivant = g_alloc;
        g_alloc = nouveau;
    }
}

void supprimer_allocation(void* ptr)
{
    Alloc** buff = &g_alloc;
    while(*buff != NULL)
    {
        if((*buff)->ptr == ptr)
        {
            Alloc* a_supprimer = (*buff);
            *buff = a_supprimer->suivant;
            free(a_supprimer);
            return;
        }
        buff = &((*buff)->suivant);
    }
    printf("Erreur : Element non trouve pour le free\n");
}

int chercher_allocation(void* ptr)
{
    Alloc* buff = g_alloc;
    while(buff != NULL)
    {
        if(buff->ptr == ptr)
            return 1;
        buff = buff->suivant;
    }
    return 0;
}
