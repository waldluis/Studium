#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array1[2], array2[2];
    do
    {
        einlesen(1, array1);
        einlesen(2, array2);

        if (array1[1] != array2[0])
        {
            printf("Spalte von Matrix A muss gleich Zeile von Matrix B sein\n");
        }
    }
    while(array1[1] != array2[0]);

    double matrixA[array1[0] * array1[1]];
    double matrixB[array2[0] * array2[1]];
    double matrixErg[array1[0] * array2[1]];

    printf("\nEingabe der 1. Matrix \n");
    matrixEinlesen(matrixA, array1);
    printf("\nEingabe der 2. Matrix \n");
    matrixEinlesen(matrixB, array2);


    printf("\nMatrix A:\n");
    drucken(&matrixA, array1, array1);
    printf("\nMatrix B:\n");
    drucken(&matrixB, array2, array2);

    multiplizieren(matrixA, matrixB, array1, array2, matrixErg);


    printf("\nErgenbis:\n");
    drucken(matrixErg, array1, array2);
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
        rueck = scanf("%d,%d", &arrayeinlesen[0], &arrayeinlesen[1]);

        while((c = getchar()) != '\n' && c != EOF)
        {
            fehler++;
        }
        if (fehler != 0 || rueck != 2)
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

void matrixEinlesen(double matrix[], int groesse[2])
{

    int richtig = 0, fehler = 0, rueck;
    char c = 0;

    for(int i = 0; i < groesse[0]; i++)
    {
        for(int j = 0; j < groesse[1]; j++)
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
                {
                    fehler++;
                }
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

            matrix[i * groesse[0] + j] = zwischen;
        }
    }
}


void multiplizieren(double matrixA[], double matrixB[], int array1[2], int array2[2], double matrix_erg[])
{
    for(int a = 0; a < (array1[0] * array2[1]); a++)
    {
        matrix_erg[a] = 0;
    }

    for(int i = 0; i < array1[0]; i++)
    {
        for(int k = 0; k < array2[1]; k++)
        {
            for(int j = 0; j < array2[0]; j++)
            {
                matrix_erg[i * array2[1] + k] += matrixA[i* array1[1] + j] * matrixB[j * array2[1] + k];
            }
        }
    }
}

void drucken(double matrix[], int array1[], int array2[])
{
    for(int i = 0; i < array1[0]; i++)
    {
        for(int j = 0; j < array2[1]; j++)
        {
            printf("%10.2lf", matrix[i * array1[0] + j]);
        }
        printf("\n");
    }
}


