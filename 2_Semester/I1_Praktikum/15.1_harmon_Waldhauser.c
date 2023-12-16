#include <stdio.h>
#include <stdlib.h>

int main()
{
    double i;
    int glied;
    double reihe;
    double bruch;

    printf("Bis zu welchem Glied soll die harmonische Reihe berechnet werden:");        //Benutzereingabe
    scanf("%d", &glied);

    for(i=1; i<=glied; i++) {                                                           //Berechnung
    bruch = 1/i;                                                                        //Berechnung des neuen Summanden
    reihe = reihe + bruch;  }

    printf("Summe bis 1/%d: %f", glied, reihe);                                         //Ausgabe
    return 0;
}
