/**********************************************************************\
* Kurzbeschreibung: complex.h
* Bietet Funktionen zum Rechnen mit komplexen Zahlen
*
* Datum:       Autor:        Grund der Aenderung:
* 01.10.2015   Dr. Lurz      Neuerstellung
*
\**********************************************************************/
#ifndef COMPLEX_H
#define COMPLEX_H

/*--- #includes ------------------------------------------------------*/

/*--- #defines -------------------------------------------------------*/
#define ERROR_C 0.

/*--- Datentypen (typedef) -------------------------------------------*/
typedef struct t_complex {
  double real;
  double imag;
} Complex;


/*--- Prototypen globaler Funktionen ---------------------------------*/

/*--------------------------------------------------------------------*\
* Addition komplexer Zahlen: x + y
* Rueckgabe: Ergebnis im Typ "Complex"
\*--------------------------------------------------------------------*/
Complex addComplex(Complex x, Complex y);

/*--------------------------------------------------------------------*\
* Subtraktion komplexer Zahlen: x - y
* Rueckgabe: Ergebnis im Typ "Complex"
\*--------------------------------------------------------------------*/
Complex subComplex(Complex x, Complex y);

/*--------------------------------------------------------------------*\
* Multiplikation komplexer Zahlen: x * y
* Rueckgabe: Ergebnis im Typ "Complex"
\*--------------------------------------------------------------------*/
Complex mulComplex(Complex x, Complex y);

/*--------------------------------------------------------------------*\
* Division komplexer Zahlen: x / y
* Rueckgabe: Ergebnis im Typ "Complex"; im Fehlerfall 0. bzw. ERROR_C
\*--------------------------------------------------------------------*/
Complex divComplex(Complex x, Complex y);

/*--------------------------------------------------------------------*\
* Lesbar formatierte Ausgabe einer komplexen Zahl
\*--------------------------------------------------------------------*/
void printComplex(Complex z);

Complex complexEinlesen();                              //Funktion zum Einlesen der Zahlen

#endif /*COMPLEX_H*/
