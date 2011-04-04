#include "fichier.h"

int main ()
{
    Maille m;
    charger_maille("1000001.cif",&m);
    printf ("%lf",m.a);

    return 0;
}
