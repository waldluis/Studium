#include <stdio.h>
#include <stdlib.h>

int main()
{
    int zahl=-1;
    int rest;
    char c;

    while(rest!=0 || zahl < 1 || zahl > 100 )
    {
        printf("Bitte geben Sie eine gerade Zahl zwischen 1 und 100 ein:");
        scanf("%d", &zahl);
        rest= zahl%2;                                                                       //Berechnung ob zahl gerade ist

        while((c = getchar()) != '\n' && c != EOF) {}                                   //Richtigkeit der Benutzereingabe prüfen
    }

    printf("Die Eingegeben Zahl ist: %d", zahl);

    return 0;
}
