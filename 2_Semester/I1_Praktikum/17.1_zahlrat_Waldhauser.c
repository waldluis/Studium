#include <stdio.h>
#include <stdlib.h>
#include <time.h>                                                                       //ben�tigt f�r time_t

int main()
{
    int max = -1;
    int zufall;
    int rueck = 0;
    int raten;
    int i=0;
    char c, d;
    time_t t;

    printf("Dieses Programm generiert eine Zufallszahl, welche Sie dann erraten \n\n");
    srand((unsigned) time(t));                                                          //erm�glicht bessere Zufallszahlen f�r rand()

    do
    {
        printf("Wie gross soll die Zahl maximal sein?");                                //Eingabe der maximalen gr��e der Zufallszahl
        scanf("%d", &max);
        while((c = getchar()) != '\n' && c != EOF) {}                                   //Richtigkeit der Benutzereingabe pr�fen
    }
    while(max <=0);

    zufall = rand() % ( max + 1 );                                                      //Generierung der Zufallszahl mit Grenze nach oben

    do                                                                                  //Schleife zum Erraten der Zufallszahl
    {
        i++;
        do{
        printf("Dein %d. Versuch:", i);
        rueck = scanf("%d%c", &raten, &d);                                              //Kontrolle der zweiten Eingabe
        fflush(stdin);
        }while(rueck != 1 && d != '\n');

        if(zufall > raten)
        {
            printf("\t\t\t\t zu niedrig \n");
        }
        else if(zufall < raten)
        {
            printf("\t\t\t\t zu hoch \n");
        }
        else
        {
            printf("\t\t\t\t richtig geraten \n \n");
        }

    }
    while(zufall != raten);

    printf("Die Zahl war: %d \n", zufall);                                              //Ausgabe der Zufallszahl und der ben�tigten Versuche
    printf("Du hast %d Versuche gebraucht.\n", i);

    return 0;
}
