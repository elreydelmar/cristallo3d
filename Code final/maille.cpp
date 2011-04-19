#include "maille.h"

int egalite(Point A, Point B)
{
    Point diff = sub_pts(A,B);
    if(norme(diff) < EPSILON)
        return 1;
    else
        return 0;
}
