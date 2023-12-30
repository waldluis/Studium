#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reallocation.h"

int *reallocation(int *ptr, int k)                                          //Funktion zur Erweiterung des Speichers um 10
{
    int *hilfptr;
    hilfptr = malloc(sizeof(int)*(10+k));                                   //Neuen Speicher anlegen mit 10 int mehr Platz
    if(hilfptr == NULL)
    {
        printf("Speichermangel");                                           //Abbruch falls nicht genuegend Speicher vorhanden
        return(0);
    }
    hilfptr = memcpy(hilfptr, ptr, k* sizeof(int));                         //Übergeben der alten Adressen in den neuen Speicher
    free(ptr);                                                              //Freigeben des alten Speichers
    return hilfptr;
}

