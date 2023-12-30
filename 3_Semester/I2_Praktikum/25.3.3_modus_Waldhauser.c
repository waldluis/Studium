#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

void zufall(int menge, int arr[MAX]);
void drucken(int menge, int arr[MAX]);
int vergleich (const void * a, const void * b);
void modus(int anzahl, int arr[MAX]);

int main()
{
    int anzahl;
    int rueck = 0;

    do
    {
        printf("Wie viele Zufallswerte (1-1000):");                  //Eingabe der Anzahl an Zufallswerten
        rueck = scanf("%4d", &anzahl);
        fflush(stdin);
    }
    while(rueck != 1 || anzahl <= 0 || anzahl >= 1001);

    int *array = malloc(anzahl * sizeof(int));                      //Dynamische Speicherreservierung

    if(array == NULL)
    {
        printf("Speicherreservierung fehlgeschlagen");
        exit(1);
    }

    printf("Gezogene Zufallszahlen \n");                            //Ausgabe der Zufallszahlen
    zufall(anzahl, array);
    drucken(anzahl, array);

    qsort(array, anzahl, sizeof(int), vergleich);                   //Sortieren der Zufallszahlen

    printf("\nZahlen sortiert:\n");                                 //Sortierte Ausgabe der Zufallszahlen
    drucken(anzahl, array);

    modus(anzahl, array);

}

void zufall(int menge, int arr[MAX])                   //Funktion zu Befüllung des Arrays mit Zufallszahlen von 0 bis 99
{
    for(int i = 0; i < menge; i++)
    {
        arr[i] = rand() % 100;
    }
}

void drucken(int menge, int arr[MAX])                 //Funktion zum Drucken des Arrays
{
    for(int i = 0; i < menge; i++)
    {
        printf("%4d", arr[i]);
    }
    printf("\n");
}

int vergleich (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );                     //Sortierfunktion für qsort
}

void modus(int menge, int arr[MAX])
{
    int arr2[100] = {0};                                //Hilfsarray mit 100 Slots
    int haeuf = 0;
    int modus;

    for(int i = 0; i < menge; i++)                      //Zaehlen der Anzahl einer Zufallszahl
    {
        arr2[arr[i]]++;
    }

    for(int i = 0; i < 100; i++)                        //Feststellung der Häufigkeit
    {
        if(arr2[i] > haeuf)
        {
            haeuf = arr2[i];
        }
    }

    for(int i = 0; i < 100; i++)                        //Feststellung des Modus (bei gleichen Anzahlen der kleinste Wert)
    {
        if(arr2[i] == haeuf)
        {
            modus = i;
            break;
        }
    }

    printf("Modus: %d\n", modus);
    printf("Haeufigkeit: %d\n", haeuf);
    printf("Bei gleicher Haeufigkeit wird der kleinste Wert als Modus ermittelt");
}
