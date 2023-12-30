/**********************************************************************\
* Kurzbeschreibung: complex.c
* Bietet Funktionen zum Rechnen mit komplexen Zahlen
*
* Datum:       Autor:        Grund der Aenderung:
*
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

/*--- #defines -------------------------------------------------------*/

/*--- Lokale Datentypen (typedef) ------------------------------------*/

/*--- Modulglobale static Variablen ----------------------------------*/

/*--- Prototypen lokaler Funktionen ----------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

/*--------------------------------------------------------------------*\
* Addition komplexer Zahlen: x + y
* Rueckgabe: Ergebnis im Typ "Complex"
\*--------------------------------------------------------------------*/
Complex addComplex(Complex x, Complex y)
{
    Complex erg;

    erg.real = x.real + y.real;
    erg.imag = x.imag + y.imag;

    return(erg);
}

/*--------------------------------------------------------------------*\
* Subtraktion komplexer Zahlen: x - y
* Rueckgabe: Ergebnis im Typ "Complex"
\*--------------------------------------------------------------------*/
Complex subComplex(Complex x, Complex y)
{
    Complex erg;

    erg.real = x.real - y.real;
    erg.imag = x.imag - y.imag;

    return(erg);
}

/*--------------------------------------------------------------------*\
* Multiplikation komplexer Zahlen: x * y
* Rueckgabe: Ergebnis im Typ "Complex"
\*--------------------------------------------------------------------*/
Complex mulComplex(Complex y, Complex x)
{
    Complex erg;

    erg.real = x.real * y.real - x.imag * y.imag;
    erg.imag = x.real * y.imag + x.imag * y.real;

    return(erg);
}

/*--------------------------------------------------------------------*\
* Division komplexer Zahlen: x / y
* Rueckgabe: Ergebnis im Typ "Complex"; im Fehlerfall 0. bzw. ERROR_C
\*--------------------------------------------------------------------*/
Complex divComplex(Complex x, Complex y)
{
    Complex erg;

    erg.real = (x.real * y.real + x.imag * y.imag)/(y.real*y.real + y.imag*y.imag);
    erg.imag = (x.imag * y.real - x.real * y.imag)/(y.real*y.real + y.imag*y.imag);

    if(y.real*y.real + y.imag*y.imag == 0)                      //Zuweisung falls Division durch 0
    {
        erg.real = ERROR_C;
    }


    return(erg);
}

/*--------------------------------------------------------------------*\
* Lesbar formatierte Ausgabe einer komplexen Zahl
\*--------------------------------------------------------------------*/
void printComplex(Complex z)
{
    printf("%.3lf + %.3lfi\n", z.real, z.imag);
}


Complex complexEinlesen()
{
    Complex zahl;
    int rueck = 0;

    do
    {
        printf("      Realteil eingeben: ");                //Eingabe des Realteils
        rueck = scanf("%lf", &zahl.real);
        fflush(stdin);
    }
    while(rueck != 1);

    rueck = 0;

    do
    {
        printf(" Imaginaerteil eingeben: ");               //Eingabe des Imaginaerteils
        rueck = scanf("%lf", &zahl.imag);
        fflush(stdin);
    }
    while(rueck != 1);

    return(zahl);
}
