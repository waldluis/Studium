#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "kommazahl.h"

int main()
{
    int anzahl;
    int rueck = 0, i = 0;
    Kommazahl ergebnis, test;
    Kommazahl *zahlen = malloc(sizeof(Kommazahl));                              //Reservieren des Speichers für eine Kommazahl
    if(zahlen == NULL)                                                          //Abbruch falls nicht genügend Speicherplatz
    {
        printf("Speichermangel");
        return(0);
    }

    do
    {
        printf("Wie viele Kommazahlen sollen addiert werden?:");                //Eingabe der Anzahl an zu addierenden Kommazahlen
        rueck = scanf("%d", &anzahl);
        fflush(stdin);
    }
    while(rueck != 1 || anzahl <= 0);

    while(i < anzahl)                                                           //Schrittweise Einlesen der Kommazahlen
    {
        zahlen = realloc(zahlen, sizeof(Kommazahl) * (i+2));                    //Neuen Speicher für weiter Kommazahl reservieren
        zahlen[i] = kommaEinlesen(i);
        i++;
    }

    ergebnis = addieren(anzahl, zahlen);                                        //Berechnung des Ergebnisses
    test = kontroll(anzahl, zahlen);                                            //Berechnung ohne Uebertrag

    if(ergebnis.nachKomma <= 9)
        printf("\nErgebnis: %ld,00000%ld (%ld,00000%ld)", ergebnis.vorKomma, ergebnis.nachKomma, test.vorKomma, test.nachKomma);

    else if(ergebnis.nachKomma <= 99)
        printf("\nErgebnis: %ld,0000%ld (%ld,0000%ld)", ergebnis.vorKomma, ergebnis.nachKomma, test.vorKomma, test.nachKomma);      //Ausgabe je nach Vorhandenden
                                                                                                                                    //Nachkommastellen mit
    else if(ergebnis.nachKomma <= 999)                                                                                              //korrekter Anzahl an
        printf("\nErgebnis: %ld,000%ld (%ld,000%ld)", ergebnis.vorKomma, ergebnis.nachKomma, test.vorKomma, test.nachKomma);        //Nullen nach dem Komma

    else if(ergebnis.nachKomma <= 9999)
        printf("\nErgebnis: %ld,00%ld (%ld,00%ld)", ergebnis.vorKomma, ergebnis.nachKomma, test.vorKomma, test.nachKomma);

    else if(ergebnis.nachKomma <= 99999)
        printf("\nErgebnis: %ld,0%ld (%ld,0%ld)", ergebnis.vorKomma, ergebnis.nachKomma, test.vorKomma, test.nachKomma);

    else
        printf("\nErgebnis: %ld,%ld (%ld,%ld)", ergebnis.vorKomma, ergebnis.nachKomma, test.vorKomma, test.nachKomma);

    return 0;
}

