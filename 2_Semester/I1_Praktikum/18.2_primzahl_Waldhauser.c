#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, zahl;
    int obere = 0, untere = 0;
    int nichtPrim = 0;
    int counter = 0;
    char c;

    printf("Programm, welches die Primzahlen in einem von Ihnen bestimmten Intervall ausgibt.\n\n");

    while(untere < 1)
    {
        printf("Untere Grenze:");                                                           //Eingabe der unteren Grenze
        scanf("%d", &untere);
        while((c = getchar()) != '\n' && c != EOF) {}                                       //Prüfung der Eingabe
    }


    while(obere < untere)                                                                   //Kontrolle des Intervalls
    {
        printf("Obere Grenze:");                                                            //Eingabe der oberen Grenze
        scanf("%d", &obere);
        while((c = getchar()) != '\n' && c != EOF) {}                                       //Prüfung der Eingabe
    }

    zahl = untere;
    printf("\n\n");

    while(zahl < obere)                                                                     //Schleife zur Erhöhung der Zahl
    {
        for (i = 2; i <= zahl /2 ; ++i)                                                        //Hochzählen der Teilers
        {
            if (zahl % i == 0)                                                              //Schleife ob Primzahl
            {
                nichtPrim = 1;
                break;
            }
        }

        if (zahl == 1)                                                                      //Falls die Zahl 1 ist
        {
            printf("       (1),");
        }
        else if (nichtPrim == 0)                                                            //Ausgabe der Primzahl
        {
            printf("%7d,", zahl);
            counter++;

            if(counter == 10)                                                               //Neue Zeile nach 10 Primzahlen
            {
                printf("\n");
                counter = 0;
            }
        }

        zahl++;                                                                             //Erhöhung der zu testenden Zahl
        nichtPrim=0;                                                                        //Rücksetzen der Bedingung zur Ausgabe
    }

    return 0;
}
