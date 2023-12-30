#ifndef KOMMAZAHL_H_INCLUDED
#define KOMMAZAHL_H_INCLUDED

typedef struct kommazahl                    //Definition der Struktur Kommazahl
{
    long vorKomma;
    long nachKomma;                         //long um 6 Nachkommastellen zu realisieren
} Kommazahl;

Kommazahl kommaEinlesen(int i);
Kommazahl addieren(int j, Kommazahl zahl[j]);
Kommazahl kontroll(int n, Kommazahl zahl[n]);

#endif // KOMMAZAHL_H_INCLUDED

