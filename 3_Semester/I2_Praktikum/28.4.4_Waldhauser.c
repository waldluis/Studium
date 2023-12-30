#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct person
{
    char nachname[20];
    char vorname[20];
    int note;
} Schueler;

void drucken(Schueler liste[MAX], int menge);

int main()
{
    Schueler liste[MAX];
    char hilf1[20], hilf2[20];
    int hilfnote, rueck = 0, anzahl = 1, summe_noten = 0;
    int noten_anzahl[6] = {0,0,0,0,0,0};
    double durchschnitt;

    printf("Eingabe der Namen mit Noten:\n");
    printf("(Ende mit leerem Nachnamen)\n");
    printf("(Maximal 50 Schueler)\n\n");

    while(1)
    {
        printf("\nEingabe des %d. Schuelers\n", anzahl);

        printf("Nachname:   ");
        fgets(hilf1, 20, stdin);
        hilf1[strlen(hilf1)-1] = '\0';                           //Abschneiden von '\n'
        fflush(stdin);

        if (strlen(hilf1) == 0)                                  //Abbruch falls kein Name eingegeben wurde
            break;

        printf("Vorname:    ");
        fgets(hilf2, 20, stdin);
        hilf2[strlen(hilf2)-1] = '\0';                           //Abschneiden von '\n'

        do
        {
            printf("Note:       ");
            rueck = scanf("%d", &hilfnote);
            fflush(stdin);
        }
        while(rueck != 1 || !(hilfnote > 0 && hilfnote < 7));

        strcpy(liste[anzahl -1].nachname, hilf1);                //Speichern der Eingaben in das Array
        strcpy(liste[anzahl -1].vorname, hilf2);
        liste[anzahl -1].note = hilfnote;

        anzahl++;
        summe_noten += hilfnote;
        noten_anzahl[hilfnote-1]++;                              //Hochzaehlen der Notenverteilung

        if(anzahl == MAX -1)                                     //Abbruch wen Array voll ist
            break;
    }

    drucken(liste, anzahl);                                      //Ausgabe des Arrays
    durchschnitt = (float)summe_noten/(anzahl-1);                //1 Abziehen wegen automat. erhoehung von Anzahl vor neuer Eingabe
    printf("\nNotendurchschnitt: %.2lf\n", durchschnitt);        //Ausgabe des Durchschnitts

    for(int i = 0; i < 6; i++)                                   //Ausgabe der Notenverteilung
    {
        printf("Note %d:", i+1);
        for(int j = 0; j < noten_anzahl[i]; j++)
            printf("*");

        printf("\n");
    }
}

void drucken(Schueler liste[MAX], int menge)
{
    printf("\n\n");
    for(int i = 0; i < menge-1; i++)
        printf("%d. %-20s, %-20s,  %d\n", i+1, liste[i].nachname, liste[i].vorname, liste[i].note);
}
