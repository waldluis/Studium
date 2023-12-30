/**********************************************************************\
* Kurzbeschreibung:
* "Funktionstest" - Matrizen mit Werten erzeugen
* und alle implementierten Funktionen aus matrixOp.c zum Test aufrufen
*
* Datum:     Autor:
*
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS //VC++: keine scanf() Warnungen
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrixOp.h"

/*--- #defines -------------------------------------------------------*/

/*--- Lokale Datentypen (typedef) ------------------------------------*/

/*--- Modulglobale static Variablen ----------------------------------*/

/*--- Prototypen lokaler Funktionen ----------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

/*--- main -----------------------------------------------------------*/
int main(void)
{
    int zeilen, spalten, rueck = 0;
    float elemEingabe;
    Matrix MatA, MatB, MatC;

    printf("Test verschiedener Funktionen der Matrixbibliothek\n");

    do
    {
        printf("Bitte Matrixgroesse eingeben (Zeilen,Spalten):");                   //Matrixgroesse einlesen
        rueck = scanf("%d,%d", &zeilen, &spalten);
        fflush(stdin);
    }
    while(rueck != 2 || zeilen < 1 || spalten < 1);

    printf("Erstes Element eingeben (Rest wird mit +1 gefuellt)\n");                //Startwert fuer automatische Generierung
    rueck = 0;
    do
    {
        printf("Wert in [1,1] (z.B. : 2.5):");
        rueck = scanf("%f", &elemEingabe);
        fflush(stdin);
    }
    while(rueck != 1);

    printf("\nTest createMatrixZero:\n");                                           //ZeroMatrix
    printf("A[%d,%d]:\n", zeilen, spalten);
    MatA = createMatrixZero(spalten, zeilen);                                       //Erstellen Matrix A
    printMatrix(MatA);

    printf("\nTest createMatrixRand:\n");                                           //RandMatrix
    printf("A[%d,%d]:\n", zeilen, spalten);
    MatA = createMatrixRand(spalten, zeilen);
    printMatrix(MatA);

    printf("\nTest eingegebenem Startwert:\n");                                          //Generierung mit +1
    printf("\nA[%d,%d]:\n", zeilen, spalten);

    for(int i = 0; i < zeilen * spalten; i++)                                       //Matrix mit +1 von Startwert befuellen
        MatA.mElement[i] = elemEingabe++;
    printMatrix(MatA);

    printf("\nB[%d,%d]:\n", zeilen, spalten);
    MatB = createMatrixZero(spalten, zeilen);                                       //Erstellen Matrix B
    MatB = copyMatrix(MatA);                                                        //Copy A nach B
    printMatrix(MatB);

    printf("\nC[%d,%d] = A + B:\n", zeilen, spalten);            //A+B
    MatC = createMatrixZero(spalten, zeilen);                                       //Erstellen Matrix C
    MatC = addMatrix(MatA, MatB);
    printMatrix(MatC);

    printf("\nC[%d,%d] = A - B:\n", zeilen, spalten);            //A-B
    MatC = subMatrix(MatA, MatB);
    printMatrix(MatC);

    destroyMatrix(&MatC);
    MatC = createMatrixZero(zeilen, spalten);                                       //Erstellen Matrix C mit groesse B^T
    MatC = transposeMatrix(MatB);

    destroyMatrix(&MatB);                                                           //loeschen von B
    MatB = createMatrixZero(zeilen, spalten);                                       //erstellen von B mit groeße B^T
    MatB = copyMatrix(MatC);                                                        //Copy C nach B

    printf("\nC[%d,%d] = B^T:\n", MatC.zeilen, MatC.spalten);
    printf("B[%d,%d] = C:\n", MatB.zeilen, MatB.spalten);
    printMatrix(MatC);

    destroyMatrix(&MatC);                                                           //loeschen von C
    MatC = createMatrixZero(spalten, spalten);                                      //erstellen von C mit "groesse A*B^T"

    MatC = multMatrix(MatA, MatB);                                                  //A*B^T
    printf("\nC[%d,%d] = a * b \n", MatC.zeilen, MatC.spalten);
    printMatrix(MatC);

    double determinante = determMatrix(MatC);

    if(determinante == ERROR)
        printf("\nDeterminante nur fuer 2x2 Matrix");

    else printf("\nDet(C) = %.2lf", determinante);



}
