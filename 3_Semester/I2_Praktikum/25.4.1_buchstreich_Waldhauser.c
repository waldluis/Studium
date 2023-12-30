#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1001

void loeschen(char str[MAX], char zeichEntf);

int main()
{
    char satz[MAX];
    printf("Bitte eine Zeichenkette eingeben (max. 1000 Zeichen):");         //Einlesen des strings
    fgets(satz, 1000, stdin);

    char zeichen;
    int rueck = 0;
    do
    {
        printf("Welches Zeichen soll geloescht werden?");                   //Einlesen der zu entfernenden Zeichens
        rueck = scanf("%1c", &zeichen);
    }
    while(rueck == 1 && zeichen == '\n');

    loeschen(satz, zeichen);

    return 0;
}

void loeschen(char string[MAX], char zeichEntf)                             //Funktion zum entfernen des Zeichens
{
    char *hilf;                                                             //Hilfspointer

    for(int i = 0; string[i] != '\0'; i++)                                  //Durchlaufen des strings
    {
        if(string[i] == zeichEntf)
        {
            hilf = &string[i+1];                                            //Setzen der Quelle zum verbschieben des Strings
            string[i] = 0;                                                  //Loeschen des Zeichens
            strcat(string, hilf);                                           //Nachschieben des Strings
            i--;
        }
    }
    printf("%s", string);
}
