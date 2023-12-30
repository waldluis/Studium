#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void umwandeln(int a)
{
    int rest, haelfte;

    rest = fabs(a % 2);                     //Betrag um Ausgabe von Minuszeichen zu vermeiden
    haelfte = a / 2;

    if(a != 0)
    {
        umwandeln(haelfte);
        printf("%1d", rest);
    }
}


int main()
{
    int zahl, rueck = 0;

    do
    {
        printf("Bitte eine Dezimalzahl eingeben:");         //Benutzereingabe
        rueck = scanf("%d", &zahl);
        fflush(stdin);
    }
    while(rueck != 1);

    umwandeln(zahl);

    if(zahl < 0)
    {
        printf("\nGibt negative Zahlen nur Betragsmaessig aus\n");      //Erklärung für negative Zahlen
    }

    return 0;
}
