#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int vielmax(int zahl1,...)
{
    va_list arg_zeiger;
    int max, wert;

    max = zahl1;

    va_start(arg_zeiger, zahl1);

    while((wert = va_arg(arg_zeiger, int)) != 0)                          //Schleife fuer max Zahl
        if(wert > max)
        {
            max = wert;
        }

    va_end(arg_zeiger);
    return max;
}

int main()
{
    printf("Testprogramm fuer vielmax() \n\n\n");

    int max;

    max = vielmax(12, 17, 3, 6, 24, 8, 0);
    printf("Die Maximale Zahl von 12, 17, 3, 6, 24, 8 ist: %d \n", max);                //Testlaufe fuer Funktion

    max = vielmax(105, 77, 54, 0);
    printf("Die Maximale Zahl von 105, 77, 54 ist: %d \n", max);

    max = vielmax(122, 7, 34, 6, 24, 8, 56, 205, 0);
    printf("Die Maximale Zahl von 122, 17, 3, 6, 24, 8, 56, 205 ist: %d \n", max);

    return 0;
}
