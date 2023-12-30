#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {Natronlauge, Kalilauge, Kalkwasser}lauge;
typedef enum {Salzsaeure, Schwefelsaeure, Salpetersaeure, Kohlensauere}saeure;

void mischen(int a, int b);

char *lau[] = {"Natronlauge ", "Kalilauge ", "Kalkwasser "};                                //Pointer zur einfacheren Ausgabe der Tabelle
char *saeu[] = {"Salzsaeure ", "Schwefelsaeure ", "Salpetersaeure ", "Kohlensauere "};

int main()
{
    char strich[] = {"-----------------"};

    printf("%17s|", " ");

    for(int i = 0; i < 4; i++)                                                  //Ausgabe der ersten Zeile
        printf("%17s|", saeu[i]);

    printf("\n");

    for(int i = 0; i < 5; i++)
        printf("%17s|", strich);                                                //Abtrennung zum Inhalt der Tabelle

    printf("\n");

    for(int i = 0; i < 3; i++)
    {
        printf("%17s|", lau[i]);                                                //Ausgabe der jeweiligen Saeure

        for(int j = 0; j < 4; j++)
            mischen(i, j);                                                      //Ausgabe der jeweiligen Mischprodukte

        printf("\n");
    }
    return 0;
}

void mischen(int a, int b)
{
    switch(a)
    {
        case Natronlauge: printf(" Natrium"); break;                            //Ausgabe des Laugenanteils des Produkts
        case Kalilauge: printf("  Kalium"); break;
        case Kalkwasser: printf(" Calcium"); break;
    }

    switch(b)
    {
        case Salzsaeure: printf("chlorid  "); break;                            //Ausgabe des Saeurennanteils des Produkts
        case Schwefelsaeure: printf("sulfat   "); break;
        case Salpetersaeure: printf("nitrat   "); break;
        case Kohlensauere: printf("carbonat "); break;
    }
    printf("|");
}
