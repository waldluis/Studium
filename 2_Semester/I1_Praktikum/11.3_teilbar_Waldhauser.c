#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Programm zum Testen, ob die Zahl x durch die Zahl y teilbar ist \n");

    int x, y, rest;

    printf("x:");
    scanf("%d", &x);
    printf("y:");
    scanf("%d", &y);

    rest=x%y;

    if (rest==0)
        {printf("%d ist durch %d teilbar", x, y);}
    else
        {printf("%d ist nicht durch %d teilbar", x, y);}

    return 0;
}
