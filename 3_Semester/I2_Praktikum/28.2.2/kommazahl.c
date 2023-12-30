#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "kommazahl.h"

Kommazahl kommaEinlesen(int i)
{
    Kommazahl zahl;
    char string[50], hilf[25];
    int richtig = 0, hilf_anz = 0, anzahl_null = 0;
    char needle[] = ",";

    do
    {
        printf("%d. Zahl eingeben(maximal 6 Nachkommastellen)(kein Nachkomma -> ,0):", i+1);
        fgets(string, 50, stdin);//Einlesen der Kommazahl

        if(strstr(string, needle))                                                      //Test ob Komma in string vorhanden
        {
            richtig = 1;
            for(int i = 0; i < strlen(string); i++)                                     //Durchlaufen des strings bis Komma
            {
                if(string[i] == ',')
                {
                    strncpy(hilf, string, i);                                           //Vorkommateil umkopieren
                    anzahl_null = i+1;                                                  //Anzahl an Stellen vor erster Kachkommazahl plus Komma
                    hilf[i] = '\0';                                                     //Kommma durch 0 ersetzen

                    for(int j = 0; j < anzahl_null; j++)                                //Alle Vorkommastellen durch 0 ersetzen
                        string[j] = '0';

                    for(int k = 0; k < strlen(string); k++)
                    {
                        if(string[k] != '0')                                            //Zaehlen der Nullen bis erste Nachkommaziffer !=0
                            break;

                        hilf_anz++;
                    }

                    hilf_anz--;                                                         //Komma nicht mitzaehlen
                    anzahl_null = hilf_anz - strlen(hilf);                              //Aanzahl der Vorkommastellen abziehen
                    zahl.vorKomma = atoi(hilf);                                         //Umwandeln der strings in int Werte
                    zahl.nachKomma = atoi(string);                                      //Falls keine Zahlen vorhanden wird 0 zurueckgegeben
                    break;
                }
            }
            fflush(stdin);
        }
        else richtig = 0;                                                               //Falls kein Komma im string enthalten ist
    }
    while(richtig != 1 || (zahl.vorKomma < -1 || zahl.nachKomma < -1));

                            //2 Nullen nach Komma ergeben Nachkommazahl kleiner 1000 entspricht 0,00x
    while(zahl.nachKomma < (100000 / (int)pow(10, anzahl_null)) && zahl.nachKomma != 0)    //Nachkommazahlen auf richtigen Wert berechnen
                zahl.nachKomma = zahl.nachKomma *10;

    return(zahl);
}

Kommazahl addieren(int j, Kommazahl zahl[j])
{
    Kommazahl erg;
    int uebertrag = 0;

    erg.nachKomma = 0;                                                              //Nullsetzen des Ergebnisses
    erg.vorKomma = 0;

    for(int i = 0; i < j; i++)
    {
        erg.nachKomma = erg.nachKomma + zahl[i].nachKomma;                          //Addieren der Nachkommastellen

        if(erg.nachKomma >= 1000000)                                                //Beachtung des Uebertrags
        {
            erg.nachKomma = erg.nachKomma - 1000000;
            uebertrag++;
        }
    }

    for(int i = 0; i < j; i++)
        erg.vorKomma = erg.vorKomma + zahl[i].vorKomma;                             //Addieren der Vorkommastellen


    erg.vorKomma = erg.vorKomma + uebertrag;                                        //Addieren des Uebertrags auf die Vorkommastellen

    return(erg);
}

Kommazahl kontroll(int n, Kommazahl zahl[n])                                        //Funktion zum berechnen ohne Uebertrag
{
    Kommazahl kontrll;

    kontrll.vorKomma = 0;                                                           //Nullsetzen des Ergebnisses
    kontrll.nachKomma = 0;

    for(int i = 0; i < n; i++)
        kontrll.nachKomma = kontrll.nachKomma + zahl[i].nachKomma;                  //Addieren der Nachkommastellen

    for(int i = 0; i < n; i++)
        kontrll.vorKomma = kontrll.vorKomma + zahl[i].vorKomma;                     //Addieren der Vorkommastellen

    return(kontrll);
}

