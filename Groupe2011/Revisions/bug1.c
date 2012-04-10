#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Ceci est un programme qui ne compile pas\n");
    int i;
    for(i=0, i<9, i++)
    {
        printf("%d\n",i);
    }

    return 0;
}
