#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Ceci est un programme qui bug\n");
    int i;
    double reel;

    for(i=0; i<9; i++)
    {
        printf("%d\n",i);
        printf("%lf\n", reel);
    }

    return 0;
}
