#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void einlesen(char string[10], int zahl, int *farb_zahl);


int main()
{
    char mischen[3][3][8] =                                                     //Mischfarben Initialisierung
    {
        {"gruen", "gelb", "blau"},
        {"gelb",  "rot",  "purpur"},
        {"blau",  "purpur", "violett"}
    };

    char wahl1[10], wahl2[10];
    int anzahl = 1, farbe1, farbe2;

    einlesen(wahl1, anzahl, &farbe1);                                           //Einlesen der Grundfarben
    einlesen(wahl2, anzahl+1, &farbe2);

    printf("Ihre Grundfarben ergeben %s.\n", mischen[farbe1][farbe2]);          //Ausgabe der gemischten Farbe
    return 0;
}

void einlesen(char string[10], int zahl, int *farb_zahl)
{
    char gruen[8] = "gruen\n";                                                  //Strings zum Prüfen der Eingabe
    char rot[6] = "rot\n";                                                      //\n wegen fgets
    char violett[10] = "violett\n";
    *farb_zahl = -1;                                                            //Initialisierung zur Fehlervermeidung

    do
    {
        printf("%d. Grundfarbe (gruen, rot, violett):", zahl);
        fgets(string, 10, stdin);
        fflush(stdin);

        if(strcmp(gruen, string) == 0)                                          //Vergleich der Eingabe mit obigen Strings
            *farb_zahl = 0;                                                     //Zuweisen einer Zahl zu jeder Farbe

        else if(strcmp(rot, string) == 0)
            *farb_zahl = 1;

        else if(strcmp(violett, string) == 0)
            *farb_zahl = 2;
    }
    while(*farb_zahl != 0 && *farb_zahl != 1 && *farb_zahl != 2);


}


