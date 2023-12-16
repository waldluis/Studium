#include <stdio.h>
#include <stdlib.h>

int main()
{
    int personen;
    int hand=0;
    int i;
    int zwischen;

    printf("Programm zum Berechnen der Anhzahl an Haendeschuettelvorgaengen auf einer Party \n\n");
    printf("Anzahl der Personen auf der Party:");
    scanf("%d", &personen);

    for(i=1; i<=personen; ++i)
    {
        hand = (hand + (personen-i));
    }                                                   //da eine Person nur den anderen die Hand schütteln
    //kann, wird i für jeden Durchlauf abgezogen

    printf("Es werden %d mal die Haende geschuettelt.\n", hand);
    return 0;
}
