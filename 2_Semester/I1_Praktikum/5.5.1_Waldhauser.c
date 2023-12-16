#include <stdio.h>
#include <stdlib.h>

int main()
{
    int wert;

    //Teilaufgabe 1
    short x=7;
    wert=1 && (~x & 0x0001);
    printf("1. Wert: %d\n", wert);


    //Teilaufgabe 2
    unsigned short u=256;
    wert=1 && (u & 0xff00);
    printf("2. Wert: %d\n", wert);

    //Teilaufgabe 3
    u=520;
    wert= 1 && (u & 0x0200);
    printf("3. Wert: %d\n", wert);

    //Teilaufgabe 4
    x=120;
    wert= 1 && (~x & 0xff80);
    printf("4. Wert: %d\n", wert);

    //Teilaufgabe 5
    u=43;
    wert= 1 && (~u & 0x0003);
    printf("5. Wert: %d\n", wert);

    return 0;
}
