#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int einlesen(int j);
void tauschen(int *a, int *b, int *t);

int main()
{
    int zahl1, zahl2, zahl3, zahl4;
    int i = 1;

    printf("Programm zum Sortieren von 4 Integer Zahlen \n\n\n");                       //Einlesen der Zahlen

    zahl1 = einlesen(i);
    i++;
    zahl2 = einlesen(i);
    i++;
    zahl3 = einlesen(i);
    i++;
    zahl4 = einlesen(i);

    if( zahl1 < zahl2 && zahl2 < zahl3 && zahl3 < zahl4)
    {
        printf("Zahlen sind schon sortiert!!! \n");
    }
    else
    {
        int tausch, i = 0 ;
        int zwischen;

        do
        {
            tausch = 0;

            if(zahl1 > zahl2)
            {
                tauschen(&zahl1, &zahl2, &tausch);
            }
            if(zahl2 > zahl3)
            {
                tauschen(&zahl2, &zahl3, &tausch);
            }
            if(zahl3 > zahl4)
            {
                tauschen(&zahl3, &zahl4, &tausch);
            }
            if(tausch == 1)
            {
                i++;
                printf("%d. Durchlauf: \nZahl 1: %d \nZahl 2: %d \nZahl 3: %d \nZahl 4: %d \nWeiter mit enter", i, zahl1, zahl2, zahl3, zahl4);
                tausch = 0;
                fflush(stdin);
                getchar();

                if( zahl1 < zahl2 && zahl2 < zahl3 && zahl3 < zahl4)
                {
                    printf("Fertig nach %d. Durchlauf.", i);
                    break;
                }
            }
        }
        while(tausch == 0);
    }
    fflush(stdin);
    return 0;
}

int einlesen(int j)                                                                         //Einlesen der Zahlen
{
    int zahl, fehler = 0, richtig = 0;
    char c;

    do
    {
        richtig = 0;
        printf("Zahl %d:", j);
        scanf("%d", &zahl);

        while((c = getchar()) != '\n' && c != EOF)
        {
            fehler++;
        }
        if (fehler != 0)
        {
            printf("Eingabe falsch bitte Wiederholen \n");                              //Kontrolle der Eingabe
            fehler = 0;
            richtig = 1;
        }
        else
        {
            richtig = 1;
            break;
        }
    }
    while(richtig == 1);

    return zahl;

}

void tauschen(int *a, int *b, int *t)
{
    int c;

    c = *a;
    *a = *b;
    *b = c;
    *t = 1;
}

