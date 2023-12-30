#include <stdio.h>
#include <stdlib.h>

int datum_richtig(int t, int m, int j, int schalt, int monat_t[][13]);
int schaltjahr_pruef(int j);
int nummer_richtig(int tag_nr, int j, int schalt);
void tagesnummer(int t, int m, int j, int monat_t[][13], int schalt);
void datum(int t_nummer, int j, int monat_t[][13], int schalt);

int main()
{
    int monat_tage[][13] =                                                              //Initialisierung des Arrays der Tagesanzahlen
    {
        { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };

    int auswahl = -1, tag = 0, monat = 0, jahr = 0, tag_nummer = 0;
    int rueck1 = 0, richtig, schalt_jahr = 0;

    do
    {
        printf("0   Ende\n1   Tagesnummer zu Datum bestimmen\n2   Datum zu Tagesnummer bestimmen\n\nIhre Wahl:");
        rueck1 = scanf("%1d", &auswahl);
        fflush(stdin);                                                                  //Menue mit Wahlmoeglichkeit
        richtig = 0;

        if(auswahl == 0)
            return 0;

        if(auswahl == 1)                                                                //Eingabe und Pruefung des Datums
        {
            int rueck2 = 0;
            do
            {
                printf("Bitte Datum eingeben (tt.mm.jjjj):");
                rueck2 = scanf("%2d.%2d.%5d", &tag, &monat, &jahr);
                fflush(stdin);
                schalt_jahr = schaltjahr_pruef(jahr);                                   //Pruefung ob Schaltjahr
                richtig = datum_richtig(tag, monat, jahr, schalt_jahr, monat_tage);     //Pruefung der Tagesanzahl und Monat
            }
            while(rueck2 != 3 || richtig != 1);
            tagesnummer(tag, monat, jahr, monat_tage, schalt_jahr);                     //Aufruf der Funktion zur Berechnung Tagesnummer
        }

        if(auswahl == 2)
        {
            int rueck3 = 0;
            do                                                                          //Eingabe und Pruefung der Tagesnummer
            {
                printf("Bitte Tagesnummer und Jahr eingeben (nr,jahr):");
                rueck3 = scanf("%3d,%4d", &tag_nummer, &jahr);
                fflush(stdin);
                schalt_jahr = schaltjahr_pruef(jahr);                                   //Pruefung ob Schaltjahr
                richtig = nummer_richtig(tag_nummer, jahr, schalt_jahr);                //Pruefung ob Tageszahl gueltig
            }
            while(rueck3 != 2 || richtig != 1);
            datum(tag_nummer, jahr, monat_tage, schalt_jahr);                           //Aufruf der Funktion zur Berechnung des Datums
        }
    }
    while(rueck1 != 0  || 0 >= auswahl || auswahl >= 2);
    return 0;
}

void tagesnummer(int t, int m, int j, int monat_t[][13], int schalt)
{
    int nummer = t;                                                                     //Tage aus Monat uebernehmen

    for(int i = 0; i <= m-1; i++)
        nummer = nummer + monat_t[schalt][i];                                           //Addieren der Tage voller Monate

    printf("%d.%d.%d ist der %d. Tag im Jahr\n\n", t, m, j, nummer);                    //Ausgabe der Tagesnummer
}

void datum(int t_nummer, int j, int monat_t[][13], int schalt)
{
    int i = 0;
    int hilf = t_nummer;

    while(t_nummer > monat_t[schalt][i+1])                                              //Abziehen der vollstaendigen Monate
    {
        t_nummer = t_nummer - monat_t[schalt][i+1];
        i++;                                                                            //Hochzaehlen von i was Monaten entspricht
    }
    printf("Der %d. Tag im Jahr = %d.%d.%d\n\n", hilf, t_nummer, i+1, j);               //Ausgabe des Datums
}

int datum_richtig(int t, int m, int j, int schalt, int monat_t[][13])
{
    int richtig = 0;

    if(schalt == 0)
    {
        if(t <= monat_t[0][m])                                                          //Pruefung ob Tage und Monat uebereinstimmen
            richtig = 1;

    }

    if(schalt == 1)                                                                     //Pruefung ob Tage und Monat uebereinstimmen im Schaltjahr
    {
        if(t <= monat_t[1][m])
            richtig = 1;

    }

    if(t < 1 || m < 1 || m > 12 || j < 1)                                               //Test ob Datum allgemein richtig ist
        richtig = 0;

    return richtig;
}

int schaltjahr_pruef(int j)                                                             //Test ob Schaltjahr vorhanden ist
{
    int schalt = 0;
    if(j %400 == 0)
        schalt = 1;

    else if(j %100 == 0)
        schalt = 0;

    else if(j %4 == 0)
        schalt = 1;

    else schalt = 0;
    return schalt;
}

int nummer_richtig(int tag_nr, int j, int schalt)                                       //Test ob Tagesnummer zu Jahreszahl passt
{
    int richtig = 0;

    if((schalt == 0 && tag_nr <= 365) || (schalt == 1 && tag_nr <= 366))
        richtig = 1;

    if(tag_nr < 1  || j < 1)                                                            //Test ob Tagesnummer und Jahr groeßer Null
        richtig = 0;

    return richtig;
}
