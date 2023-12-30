/**********************************************************************\
* Kurzbeschreibung: matrixOp.c
* Bietet Funktionen fuer Operationen mit Matrizen
*
* Datum:       Autor:        Grund der Aenderung:
*
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrixOp.h"

/*--- #defines -------------------------------------------------------*/

/*--- Lokale Datentypen (typedef) ------------------------------------*/

/*--- Modulglobale static Variablen ----------------------------------*/

/*--- Prototypen lokaler Funktionen ----------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

/*--------------------------------------------------------------------*\
* Erstellt eine neue Matrix (cM)
*  - reserviert lediglich den notwendigen Speicher
*  - dynamische Verwaltung von Speicher muss mit malloc() und free()
*    durchgeführt werden; dynamische Arrays sind nicht erlaubt !!!
\*--------------------------------------------------------------------*/
Matrix createMatrix(unsigned int spalten, unsigned int zeilen)
{
    Matrix mat;

    mat.mElement = ((float*)malloc(sizeof(float) * spalten * zeilen));

    if(mat.mElement == NULL)
    {
        printf("Kein freier Speicher");
        exit(1);
    }

    mat.spalten = spalten;
    mat.zeilen = zeilen;

    return(mat);
}

/*--------------------------------------------------------------------*\
* Erstellt und initialisiert eine neue Matrix (zM)
* - reserviert den notwendigen Speicher
* - befuellt die Matrix mit 0
\*--------------------------------------------------------------------*/
Matrix createMatrixZero(unsigned int spalten, unsigned int zeilen)
{
    Matrix mat = createMatrix(spalten, zeilen);                     //Erstellen der Matrix

    for(int i = 0; i < zeilen * spalten; i++)
        mat.mElement[i] = 0.0;

    return(mat);
}

/*--------------------------------------------------------------------*\
* Erstellt und initialisiert eine neue Matrix (rM)
* - reserviert den notwendigen Speicher
* - befuellt die Matrix mit Zufallszahlen
\*--------------------------------------------------------------------*/
Matrix createMatrixRand(unsigned int spalten, unsigned int zeilen)
{
    Matrix mat = createMatrix(spalten, zeilen);                      //Erstellen der Matrix

    for(int i = 0; i < zeilen * spalten; i++)
        mat.mElement[i] = ((float)rand() / 200) -50;

    return(mat);
}

/*--------------------------------------------------------------------*\
* Kopiert eine Matrix und gibt die Kopie zurueck (yM)
\*--------------------------------------------------------------------*/
Matrix copyMatrix(const Matrix toCopy)
{
    Matrix mat = createMatrix(toCopy.spalten, toCopy.zeilen);          //Erstellen der Matrix

    for(int i = 0; i < toCopy.zeilen * toCopy.spalten; i++)
        mat.mElement[i] = toCopy.mElement[i];

    return(mat);
}

/*--------------------------------------------------------------------*\
* "Loescht" eine Matrix (dM)
* - gibt reservierten Speicher wieder frei !
* - in der urspruenglichen, uebergebenen Matrix bleiben die Werte erhalten!
\*--------------------------------------------------------------------*/
void deleteMatrix(Matrix toDelete)
{
    free(toDelete.mElement);
}

/*--------------------------------------------------------------------*\
* "Loescht / Zerstoert" eine uebergegebene Matrix (ddM)
* - gibt Speicher wieder frei, setzt alle Werte auf NULL bzw. "0" !
* - Beachte Unterschiede zur vorigen Funktion !!!
\*--------------------------------------------------------------------*/
void destroyMatrix(Matrix *pToDestroy)
{
    for(int i = 0; i < pToDestroy->zeilen * pToDestroy->spalten; i++)
        pToDestroy->mElement[i] = 0.0;                      //Nullsetzen der Elemente

    pToDestroy->zeilen = 0;
    pToDestroy->spalten = 0;
    free(pToDestroy->mElement);
    pToDestroy->mElement = NULL;                            //Nullsetzten des Pointers
}

/*--------------------------------------------------------------------*\
* Gibt den Eintrag der Matrix an der Stelle (xPos, yPos) zurueck (gE)
* Rueckgabe im Fehlerfall: ERROR
\*--------------------------------------------------------------------*/
MatTyp getEntryAt(const Matrix ma, unsigned int xPos, unsigned int yPos)
{
    float wert;

    if((xPos-1) < ma.spalten && (yPos-1) < ma.zeilen)
        wert = ma.mElement[(yPos-1) * ma.spalten + (xPos-1)];         //Umrechnung von 2d- in 1d-Array

    else return ERROR;

    return(wert);
}

/*--------------------------------------------------------------------*\
* Setzt den Eintrag der Matrix an der Stelle (xPos, yPos) (sE)
* Rueckgabe: TRUE, im Fehlerfall: FALSE
\*--------------------------------------------------------------------*/
Bool setEntryAt(Matrix ma, unsigned int xPos, unsigned int yPos, MatTyp value)
{
    Bool moeglich = FALSE;

    if((xPos-1) < ma.spalten && (yPos-1) < ma.zeilen)
    {
        ma.mElement[(yPos-1) * ma.spalten + (xPos-1)] = value;
        moeglich = TRUE;
    }
    else moeglich = FALSE;

    return(moeglich);
}

/*--------------------------------------------------------------------*\
* Gibt eine Matrix im Kommandofenster "schoen formatiert" aus (pM)
\*--------------------------------------------------------------------*/
void printMatrix(const Matrix ma)
{
    for(int i = 0, z = 0; z < ma.zeilen ; z++)
    {
        printf("(");
        for(int s = 0; s < ma.spalten ; i++, s++)
            printf(" %8.2f", ma.mElement[i]);

        printf(")\n");
    }
}

/*--------------------------------------------------------------------*\
* Addiert zwei Matrizen (aM)
* Rueckgabe:
* - Ergebnis der Addition in neu erzeugter Matrix
* - Rueckgabe im Fehlerfall: Matrix der Groesse "0"
\*--------------------------------------------------------------------*/
Matrix addMatrix(const Matrix ma, const Matrix mb)
{
    Matrix mat = createMatrix(ma.spalten, ma.zeilen);

    if(ma.zeilen == mb.zeilen && ma.spalten == mb.spalten)          //Bedingung fuer Addition
    {
        for(int i = 0; i < ma.zeilen * ma.spalten; i++)
            mat.mElement[i] = ma.mElement[i] + mb.mElement[i];

        return(mat);
    }
    else return(mat = createMatrixZero(0,0));
}

/*--------------------------------------------------------------------*\
* Subtrahiert zwei Matrizen (sM)
* Rueckgabe: "ma - mb"
* - Ergebnis der Subtraktion in neu erzeugter Matrix
* - Rueckgabe im Fehlerfall: Matrix der Groesse "0"
\*--------------------------------------------------------------------*/
Matrix subMatrix(const Matrix ma, const Matrix mb)
{
    Matrix mat = createMatrix(ma.spalten, ma.zeilen);

    if(ma.zeilen == mb.zeilen && ma.spalten == mb.spalten)          //Bedingung fuer Subtraktion
    {
        for(int i = 0; i < ma.zeilen * ma.spalten; i++)
            mat.mElement[i] = ma.mElement[i] - mb.mElement[i];

        return(mat);
    }
    else return(mat = createMatrixZero(0,0));
}

/*--------------------------------------------------------------------*\
* Multipliziert zwei Matrizen (mM)
* Rueckgabe: "ma * mb"
* - Ergebnis der Multiplikation in neu erzeugter Matrix
* - Rueckgabe im Fehlerfall: Matrix der Groesse "0"
\*--------------------------------------------------------------------*/
Matrix multMatrix(const Matrix ma, const Matrix mb)
{
    Matrix mat = createMatrixZero(ma.zeilen, mb.spalten);           //Bedingung fuer Multiplikation

    if(ma.zeilen == mb.spalten)
    {
        for(int z = 1, i = 0; z <= ma.zeilen; z++)
        {
            for(int s = 1; s <= mb.spalten; s++, i++)
            {
                for(int j = 1; j <= mb.zeilen; j++)
                {
                    mat.mElement[i] += getEntryAt(ma, j, z) * getEntryAt(mb, s, j);
                }
            }
        }
        return(mat);
    }
    else return(mat = createMatrixZero(0,0));


}

/*--------------------------------------------------------------------*\
* Transponiert eine Matrix (tM)
* Rueckgabe: "ma^T"
\*--------------------------------------------------------------------*/
Matrix transposeMatrix(const Matrix ma)
{
    Matrix mat = createMatrix(ma.zeilen, ma.spalten);           //Erstellen der leeren Transponierten Matrix

    for(int s = 1; s <= ma.spalten; s++)
    {
        for(int z = 1; z <= ma.zeilen; z++)
        {
            setEntryAt(mat, z, s, getEntryAt(ma, s, z));        //Umkopieren der Werte in transponierte Matrix
        }
    }

    return(mat);
}


/*--------------------------------------------------------------------*\
* Gibt die Determinante der Matrix ma zurueck (dt)
* Rueckgabe im Fehlerfall: ERROR
* !!! Optional / Implementation freiwillig !!!
* fuer kleine Matrizen reicht ein einfacher Algorithmus
* wer moechte kann auch ein effizientes Verfahren implementieren
\*--------------------------------------------------------------------*/
double determMatrix(const Matrix ma)
{
    double det;

    if(ma.spalten == 2 && ma.zeilen == 2)
    {
        det = (ma.mElement[0] * ma.mElement[3]) - (ma.mElement[1] * ma.mElement[2]);
        return(det);
    }
    else return ERROR;
}

