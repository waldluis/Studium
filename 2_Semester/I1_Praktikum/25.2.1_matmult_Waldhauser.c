#include <stdio.h>
#include <stdlib.h>
#define MAX 15

void einlesen(int matrixzahl, int arrayeinlesen[2]);
void matrixEinlesen(int laenge[2], double matrix[MAX][MAX]);
void drucken( int groesse[], double matrix[MAX][MAX]);
void multiplizieren(int anzahlA[2], int anzahlB[2], double matA[MAX][MAX], double matB[MAX][MAX], double mat_erg[MAX][MAX]);

int main()
{
    int groesseA[2], groesseB[2], groesseErg[2];
    do
    {
        einlesen(1, groesseA);                                                          //Eingabe der Matrix Größe
        einlesen(2, groesseB);

        if (groesseA[1] != groesseB[0])
            printf("Spalte von Matrix A muss gleich Zeile von Matrix B sein\n");            //Bedingung zur Multiplikation

    }
    while(groesseA[1] != groesseB[0]);

    groesseErg[0] = groesseA[0];                                                          //Große der Ergebnis Matrix
    groesseErg[1] = groesseB[1];

    double matrixA[groesseA[0]][groesseA[1]];
    double matrixB[groesseB[0]][groesseB[1]];
    double matrixErg[groesseErg[0]][groesseErg[1]];

    printf("\nEingabe der 1. Matrix \n");                                               //Eingabe der Werte der Matrix
    matrixEinlesen(groesseA, matrixA);
    printf("\nEingabe der 2. Matrix \n");
    matrixEinlesen(groesseB, matrixB);

    printf("\nMatrix A:\n");
    drucken(groesseA, matrixA);                                                         //Ausgabe der Eingangs Matrizen
    printf("\nMatrix B:\n");
    drucken(groesseB, matrixB);

    multiplizieren(groesseA, groesseB, matrixA, matrixB, matrixErg);                    //Multiplikation

    printf("\nErgebnis:\n");
    drucken(groesseErg, matrixErg);                                                       //Ausgabe der Ergebnis Matrix
}

void einlesen(int matrixzahl, int arrayeinlesen[2])
{
    int richtig, fehler, rueck;
    char c;
    do
    {
        c = 0;
        richtig = 0;
        fehler = 0;
        printf("Zeilen,Spalten der Matrize %d:", matrixzahl);
        rueck = scanf("%d,%d", &arrayeinlesen[0], &arrayeinlesen[1]);                   //Einlesen der Größe

        while((c = getchar()) != '\n' && c != EOF )
            fehler++;

        if (fehler != 0 || rueck != 2 || arrayeinlesen[0] > MAX || arrayeinlesen[1] > MAX)                //Prüfung ob kleiner als MAX
        {
            printf("Eingabe falsch bitte Wiederholen \n");                              //Kontrolle der Eingabe
            fehler = 0;
            richtig = 0;
        }
        else
        {
            richtig = 1;
            break;
        }
    }
    while(richtig == 0);

}

void matrixEinlesen(int laenge[2], double matrix[laenge[0]][laenge[1]])
{

    int richtig = 0, fehler = 0, rueck;
    char c = 0;

    for(int i = 0; i < laenge[0]; i++)                                                         //Schleife zum Einlesen der Werte
    {
        for(int j = 0; j < laenge[1]; j++)
        {
            double zwischen;
            do
            {
                fehler = 0;
                richtig = 0;
                c = 0;
                printf("Wert fuer Zelle %d,%d:", i +1, j +1);
                rueck = scanf("%lf", &zwischen);

                while((c = getchar()) != '\n' && c != EOF)
                    fehler++;

                if (fehler != 0 || rueck != 1)
                {
                    printf("Eingabe falsch bitte Wiederholen \n");                              //Kontrolle der Eingabe
                    fehler = 0;
                    richtig = 0;
                }
                else
                {
                    richtig = 1;
                    break;
                }
            }
            while(richtig == 0);

            matrix[i][j] = zwischen;
        }
    }
}

void drucken( int groesse[], double matrix[groesse[0]][groesse[1]])
{
    for(int i = 0; i < groesse[0]; i++)
    {
        for(int j = 0; j < groesse[1]; j++)                                                     //Schleife zur Ausgabe der Matrix
            printf("%10.2lf", matrix[i][j]);

        printf("\n");
    }
}

void multiplizieren(int anzahlA[2], int anzahlB[2], double matA[anzahlA[0]][anzahlA[1]], double matB[anzahlB[0]][anzahlB[1]], double mat_erg[anzahlA[0]][anzahlB[1]])
{

    for(int i = 0; i < anzahlA[0]; i++)
    {
        for(int k = 0; k < anzahlB[1]; k++)
        {
            mat_erg[i][k] = 0;                                                              //Schleife zum Multiplizieren der Matrizen
            for(int j = 0; j < anzahlB[0]; j++)                                //Maximum von j geändert
                mat_erg[i][k] += matA[i][j] * matB[j][k];
        }
    }
}
