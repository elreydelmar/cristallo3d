#include <stdlib.h>
#include <stdio.h>
#include "maille.h"
void set_nimps(int* a);

int main()
{
    int b = 0;
    printf("%ld ", b);
    set_nimps(&b);
    printf("%ld ", b);

    return 0;
}

void set_nimps(int* a)
{
    *a=1;
}
