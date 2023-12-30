#include <stdio.h>
#include <stdlib.h>

#include "zeitaddieren.h"

unsigned long zeit_in_sek(Zeit z)
{
    unsigned long sekunden;
    unsigned long tag_sek, std_sek, min_sek;

    tag_sek = z.tag * 86400;                                    //Anzahl jeweils mit eigener Menge an Sekunden multiplzieren
    std_sek = z.stunde * 3600;
    min_sek = z.minute * 60;

    sekunden = tag_sek + std_sek + min_sek + z.sekunde;         //Einzelne Sekundenanzahlen zum Gesamten addieren

    return(sekunden);
}

Zeit sek_in_zeit(unsigned long zeit_in_sek)
{
    Zeit z;

    z.tag = zeit_in_sek / 86400;                                //Ermittlung der Tage durch Gesamte Sekunden geteilt durch Sekundenanzahl pro Tag
    zeit_in_sek = zeit_in_sek - z.tag * 86400;                  //Abziehen der Anzahl an vollstaendigen Tagen bei Gesamtsekunden

    z.stunde = zeit_in_sek / 3600;                              //gleiches Verfahren mit Stunden
    zeit_in_sek = zeit_in_sek - z.stunde * 3600;

    z.minute = zeit_in_sek / 60;                                //gleiches Verfahren mit Minuten
    zeit_in_sek = zeit_in_sek - z.minute * 60;

    z.sekunde = zeit_in_sek;                                    //Uebrige Sekunden umspeichern

    return(z);
}

Zeit zeitEinlesen(int n)                                        //Einlesen der Zeit in Struktur
{
    Zeit z;
    int richtig = 0, rueck = 0;
    do
    {
        printf("Bitte gib %d. Zeit ein (tt.hh.mm.ss):", n);
        rueck = scanf("%2d.%2d.%2d.%2d", &z.tag, &z.stunde, &z.minute, &z.sekunde);
        fflush(stdin);
        richtig = eingabeRichtig(z);
    }
    while(rueck != 4 || richtig != 1);

    return(z);
}

int eingabeRichtig(Zeit z)                                      //Funktion zum Test ob Zeit sinnvoll ist
{
    int r = 1;

    if(z.tag < 0)
        r = 0;

    if(z.stunde < 0 || z.stunde > 23)
        r = 0;

    if(z.minute < 0 || z.minute > 59)
        r = 0;

    if(z.sekunde < 0 || z.sekunde > 59)
        r = 0;

    return(r);
}
