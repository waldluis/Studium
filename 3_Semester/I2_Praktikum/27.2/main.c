#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reallocation.h"

void ausgabe(int mat[10]);

int  main()
{
    int *zahl= malloc(sizeof(int)* 10), hilf, r = 1, i = 0;

    if(zahl == NULL)                                                        //Abbruch falls nicht genügend Speicherplatz
    {
        printf("Speichermangel");
        return(0);
    }
    printf("Bitte eine Zahlenfolge eingeben (Ende mit ctrl z/d in neuer Zeile):");

    while(1)
    {
NEU:                                                                        //Sprungpunkt zum neustarten der Schleife
        hilf = getchar();                                                   //Erkennen vom Ende der Eingabe
        if(hilf == EOF)
            break;

        if(!(hilf == '0' || hilf == '1' || hilf == '2' || hilf == '3' || hilf == '4' || hilf == '5'
                || hilf == '6' || hilf == '7' || hilf == '8' || hilf == '9'))               //Ueberpruefen ob nur Zahlen
        {
            if(hilf == '\n')                                                //falls \n Sprung zum Anfang der Schleife
                goto NEU;
            else
            {
                printf("Nur Zahlen eingeben");                              //Abbruch falls keine Zahleneingabe erfolgte
                exit(1);
            }
        }

        zahl[i] = hilf;                                                     //Speichern der Zahlen in Array als char Wert (wegen getchar)
        i++;

        if(i == 10*r)
        {
            zahl = reallocation(zahl, i);                                   //Speichererweiterung falls nötig
            r++;
        }
    }
    int striche[10];                                                        //Array zum Zählen der einzelnen Zahlen

    for(int j = 0; j<10; j++)                                               //Arrayinhalte auf 0 setzen
        striche[j] = 0;

    for(int k = 0; k < i; k++)
    {
        int hilf = zahl[k] - 48;                                            //Umschreiben der char Werte in int Werte (char - 48 entspricht int Wert)
        striche[hilf]++;                                                    //Anzahl der einzelnen Ziffer erfassen
    }

    ausgabe(striche);

    return(0);
}

void ausgabe(int mat[10])
{
    for(int p = 0; p < 10; p++)
    {
        printf("\n%d: ", p);                                                //Ausgabe der jeweiligen Zahl
        if(mat[p] != 0)
        {
            for(int l = 0; l < mat[p]; l++)                                 //Ausgabe der Striche
                printf("I");
        }
    }
}
