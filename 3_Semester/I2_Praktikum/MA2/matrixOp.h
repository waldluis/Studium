/**********************************************************************\
* Kurzbeschreibung: matrixOp.h
* Bietet Funktionen fuer Operationen mit Matrizen
*
* Datum:       Autor:        Grund der Aenderung:
* 01.10.2015   Dr. Lurz      Neuerstellung
*
\**********************************************************************/
#ifndef MATRIXOP_H
#define MATRIXOP_H

/*--- #includes ------------------------------------------------------*/
#include <float.h>

/*--- #defines -------------------------------------------------------*/
#define TRUE  1
#define FALSE 0
#define ERROR FLT_MAX

/*--- Datentypen (typedef) -------------------------------------------*/
typedef float MatTyp;

typedef struct t_matrix {
  MatTyp *mElement;
  unsigned int spalten;
  unsigned int zeilen;
} Matrix;

typedef int Bool;


/*--- Prototypen globaler Funktionen ---------------------------------*/

/*--------------------------------------------------------------------*\
* Erstellt eine neue Matrix (cM)
*  - reserviert lediglich den notwendigen Speicher
*  - dynamische Verwaltung von Speicher muss mit malloc() und free()
*    durchgeführt werden; dynamische Arrays sind nicht erlaubt !!!
\*--------------------------------------------------------------------*/
Matrix createMatrix(unsigned int spalten, unsigned int zeilen);

/*--------------------------------------------------------------------*\
* Erstellt und initialisiert eine neue Matrix (zM)
* - reserviert den notwendigen Speicher
* - befuellt die Matrix mit 0
\*--------------------------------------------------------------------*/
Matrix createMatrixZero(unsigned int spalten, unsigned int zeilen);

/*--------------------------------------------------------------------*\
* Erstellt und initialisiert eine neue Matrix (rM)
* - reserviert den notwendigen Speicher
* - befuellt die Matrix mit Zufallszahlen
\*--------------------------------------------------------------------*/
Matrix createMatrixRand(unsigned int spalten, unsigned int zeilen);

/*--------------------------------------------------------------------*\
* Kopiert eine Matrix und gibt die Kopie zurueck (yM)
\*--------------------------------------------------------------------*/
Matrix copyMatrix(const Matrix toCopy);

/*--------------------------------------------------------------------*\
* "Loescht" eine Matrix (dM)
* - gibt reservierten Speicher wieder frei !
* - in der urspruenglichen, uebergebenen Matrix bleiben die Werte erhalten!
\*--------------------------------------------------------------------*/
void deleteMatrix(Matrix toDelete);

/*--------------------------------------------------------------------*\
* "Loescht / Zerstoert" eine uebergegebene Matrix (ddM)
* - gibt Speicher wieder frei, setzt alle Werte auf NULL bzw. "0" !
* - Beachte Unterschiede zur vorigen Funktion !!!
\*--------------------------------------------------------------------*/
void destroyMatrix(Matrix *pToDestroy);

/*--------------------------------------------------------------------*\
* Gibt den Eintrag der Matrix an der Stelle (xPos, yPos) zurueck (gE)
* Rueckgabe im Fehlerfall: ERROR
\*--------------------------------------------------------------------*/
MatTyp getEntryAt(const Matrix ma, unsigned int xPos, unsigned int yPos);

/*--------------------------------------------------------------------*\
* Setzt den Eintrag der Matrix an der Stelle (xPos, yPos) (sE)
* Rueckgabe: TRUE, im Fehlerfall: FALSE
\*--------------------------------------------------------------------*/
Bool setEntryAt(Matrix ma, unsigned int xPos, unsigned int yPos, MatTyp value);

/*--------------------------------------------------------------------*\
* Gibt eine Matrix im Kommandofenster "schoen formatiert" aus (pM)
\*--------------------------------------------------------------------*/
void printMatrix(const Matrix ma);

/*--------------------------------------------------------------------*\
* Addiert zwei Matrizen (aM)
* Rueckgabe:
* - Ergebnis der Addition in neu erzeugter Matrix
* - Rueckgabe im Fehlerfall: Matrix der Groesse "0"
\*--------------------------------------------------------------------*/
Matrix addMatrix(const Matrix ma, const Matrix mb);

/*--------------------------------------------------------------------*\
* Subtrahiert zwei Matrizen (sM)
* Rueckgabe: "ma - mb"
* - Ergebnis der Subtraktion in neu erzeugter Matrix
* - Rueckgabe im Fehlerfall: Matrix der Groesse "0"
\*--------------------------------------------------------------------*/
Matrix subMatrix(const Matrix ma, const Matrix mb);

/*--------------------------------------------------------------------*\
* Multipliziert zwei Matrizen (mM)
* Rueckgabe: "ma * mb"
* - Ergebnis der Multiplikation in neu erzeugter Matrix
* - Rueckgabe im Fehlerfall: Matrix der Groesse "0"
\*--------------------------------------------------------------------*/
Matrix multMatrix(const Matrix ma, const Matrix mb);

/*--------------------------------------------------------------------*\
* Transponiert eine Matrix (tM)
* Rueckgabe: "ma^T"
\*--------------------------------------------------------------------*/
Matrix transposeMatrix(const Matrix ma);

/*--------------------------------------------------------------------*\
* Gibt die Determinante der Matrix ma zurueck (dt)
* Rueckgabe im Fehlerfall: ERROR
* !!! Optional / Implementation freiwillig !!!
* fuer kleine Matrizen reicht ein einfacher Algorithmus
* wer moechte kann auch ein effizientes Verfahren implementieren
\*--------------------------------------------------------------------*/
double determMatrix(const Matrix ma);


#endif /*MATRIXOP_H*/
