#include <stdio.h>
#include <stdlib.h>

int main()
{
    char wahl;
    printf("Willkommen im Hauptmenue \n \n"
           "(A)endern \n"
           "(B)eenden \n"
           "(D)rucken \n"
           "(E)ingeben \n"
           "(L)oeschen \n \n"
           "Ihre Eingabe zum Fortfahren:");

    scanf("%c", &wahl);

    switch(wahl) {

        case 'A': printf("\n Es wird (A)endern fortgefahren");
        break;

        case 'B': printf("\n Es wird (B)eenden fortgefahren");
        break;

        case 'D': printf("\n Es wird (D)rucken fortgefahren");
        break;

        case 'E': printf("\n Es wird (E)ingeben fortgefahren");
        break;

        case 'L': printf("\n Es wird (L)oeschen fortgefahren");
        break;

        default: printf("\n %c ist eine ungueltige Eingabe", wahl);


    }

    return 0;
}
