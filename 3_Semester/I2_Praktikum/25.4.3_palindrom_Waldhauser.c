#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1001

void palindrom(int anzahl, char string[MAX]);

int main()
{
    char satz[MAX];
    int laenge;
    printf("Bitte eine Zeichenkette eingeben (max. 1000 Zeichen und entweder Klein- oder Grossbuchstaben):");
    fgets(satz, 1000, stdin);

    laenge = strlen(satz);

    satz[laenge -1] = '\0';                                     //Return vom Ende des Strings entfernen zur Fehlervermeidung

    palindrom(laenge, satz);

    return 0;
}

void palindrom(int anzahl, char string[anzahl])
{
    char trennen[] = " ";                                       //Zeichen für strtok
    char *hilf, string2[MAX];
    int flag = 0, zeichen;

    hilf = strtok(string, trennen);                             //Erstes Wort bis Leerzeichen abkapseln

    while(hilf != NULL)
    {
        strcpy(string2, hilf);                                  //Umkopieren des Wortes in Hilfsstring
        zeichen = strlen(string2);

        for(int i = 0; i < zeichen; i++)
        {
            if(string2[i] != string2[zeichen -i -1])            //Prüfung ob Buchstaben von Anfang und Ende her gleich sind
                flag = 1;
        }

        if(flag == 0)
        {
            printf("%s\n", string2);                            //Ausgabe falls Palindrom
            flag = 0;
        }
        else  flag = 0;

        hilf = strtok(NULL, trennen);                           //naechstes Wort bis Leerzeichen abkapseln
    }
}


