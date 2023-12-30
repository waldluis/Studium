/**********************************************************************\
* Kurzbeschreibung:
* "Funktionstest" - 2 komplexe Zahlen einlesen
* und alle implementierten Funktionen aus complex.c zum Test aufrufen
*
* Datum:     Autor:
*
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS //VC++: keine scanf() Warnungen
#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

/*--- #defines -------------------------------------------------------*/

/*--- Lokale Datentypen (typedef) ------------------------------------*/

/*--- Modulglobale static Variablen ----------------------------------*/

/*--- Prototypen lokaler Funktionen ----------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

/*--- main -----------------------------------------------------------*/
int main(void)
{
    Complex zahl1, zahl2, ergAdd, ergSub, ergMult, ergDiv;

    printf("1. komplexe Zahl eingeben\n");                          //Einlesen der ersten Zahl
    zahl1 = complexEinlesen();

    printf("2. komplexe Zahl eingeben\n");                          //Einlesen der zweiten Zahl
    zahl2 = complexEinlesen();

    printf("\nx = ");                                               //Ausgabe der urspruenglichen Zahlen
    printComplex(zahl1);

    printf("y = ");
    printComplex(zahl2);
    printf("\n");

    ergAdd = addComplex(zahl1, zahl2);                              //Berechnung der einzelnen Ergebnisse
    ergSub = subComplex(zahl1, zahl2);
    ergMult = mulComplex(zahl1, zahl2);
    ergDiv  = divComplex(zahl1, zahl2);

    printf("Summe:       x + y = ");                                //Ausdrucken der jeweiligen Ergebnisse
    printComplex(ergAdd);
    printf("Differenz:   x - y = ");
    printComplex(ergSub);
    printf("Produkt:     x * y = ");
    printComplex(ergMult);

    if(ergDiv.real == ERROR_C)                                       //Fehlermeldung falls Division durch 0
        printf("Division nicht moeglich!!!");

    else
    {
        printf("Quotient:    x / y = ");
        printComplex(ergDiv);
    }

}

