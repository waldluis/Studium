#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

void ziehen(int wieViele, int maxZahl);

int main()
{
    srand(time(NULL));
    int bereich, anzahl;
    int zahl[MAX];
    int richtig;
    int fehler = 0;
    char c;

    printf("Lottozahlen Simulation\n\n\n");

    do
    {
        richtig = 0;
        printf("Wie viele Kugeln sollen es sein? (min 1 bis max 100):");                    //Eingabe der Anzahl an Kugeln
        scanf("%d", &bereich);

        while((c = getchar()) != '\n' && c != EOF)
            fehler++;

        if (fehler != 0 || (bereich  <= 1 || bereich >= 101))                               //Kontrolle der Eingabe
        {
            printf("Eingabe falsch bitte Wiederholen \n");
            fehler = 0;
            richtig = 0;
        }
        else richtig = 1;
    }
    while(richtig == 0);

    do
    {
        richtig = 0;
        printf("Wie viele werden gezogen? (min 1 bis max 49):");                            //Eingabe der Anzahl der zu ziehenden Kugeln
        scanf("%d", &anzahl);

        while((c = getchar()) != '\n' && c != EOF)
            fehler++;

        if (fehler != 0 || (anzahl  <= 1 || anzahl > bereich))
        {
            printf("Eingabe falsch bitte Wiederholen \n");                                  //Kontrolle der Eingabe
            fehler = 0;
            richtig = 0;
        }
        else richtig = 1;
    }
    while(richtig == 0);

    zahl[anzahl];
    ziehen(anzahl, bereich);

}

void ziehen(int wieViele, int maxZahl)
{
    int zahlen[MAX];
    int gezogen[wieViele];
    int zwischen;
    int i;

    for(i = 0; i < wieViele; i++)
    {
        zahlen[i] = i + 1;
    }

    for (int i = 0; i < maxZahl; i++)
    {
        gezogen[i] = rand() % maxZahl;

    }

    for (int i = 0; i < wieViele; i++)
        printf(" %d \t", zahlen[i]);                                                        //Ausgabe der Zahlen
}

