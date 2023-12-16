#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Programm zur Berechnung der Fibonacci-Zahlen mit fuehrender 0 \n\n\n");

    int wert = -1;
    int zahl = 0;
    int zahlalt = -1;
    int zahlakt = 1;
    int i = 0, n = 1;
    char c, enter;

    while(wert <= 1)
    {
        printf("Bis zu welchem Wert soll berechnet werden? (Nur positive ganze Werte moeglich) ");
        scanf("%d", &wert);

        while((c = getchar()) != '\n' && c != EOF) {}                                   //Richtigkeit der Benutzereingabe prüfen

        while(wert > (zahl + zahlalt))                                                  //Berechnung der Fibonacci-Zahl
        {
            zahl = zahlalt + zahlakt;
            zahlalt = zahlakt;
            zahlakt = zahl;
            printf("%3d. %15d\n", i, zahl);
            i++;

            while(i-1 == n*20)                                                              //Unterbrechnung bei jedem 20. Wert
            {
                printf("Weiter mit Enter");
                n++;

                    while(enter != '\n')
                    {
                        scanf("%c", &enter);   //Eingabe von enter
                    }

                enter='1';                                                                  //Rücksetzen von enter
            }
        }
    }

    return 0;
}
