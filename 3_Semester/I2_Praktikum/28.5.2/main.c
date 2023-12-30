#include <stdio.h>
#include <stdlib.h>

#include "zeitaddieren.h"


int main()
{
    Zeit z1, z2, ergebnis;
    int nummer = 1;
    int sekunde1, sekunde2, sekundeGes;

    printf("Programm zum addieren von zwei Zeiten\n");

    z1 = zeitEinlesen(nummer);                                      //Einlesen der zwei Zeiten
    nummer++;
    z2 = zeitEinlesen(nummer);

    sekunde1 = zeit_in_sek(z1);                                     //Umrechnen in Sekunden
    sekunde2 = zeit_in_sek(z2);

    sekundeGes = sekunde1 + sekunde2;                               //Komplette Sekunden

    ergebnis = sek_in_zeit(sekundeGes);                             //Umrechnung in Tage, Stunden, Minuten und Sekunden

    printf("\nErgebnis: %d Tage, %d:%d.%d;   %d Sekunden insgesamt", ergebnis.tag, ergebnis.stunde, ergebnis.minute, ergebnis.sekunde, sekundeGes);

    return 0;
}
