#include <stdio.h>
#include <stdlib.h>

#define MAX 999

int ziehen(int menge, int mat[MAX]);
void drucken(int menge, int mat[MAX]);
void komprimieren(int menge, int mat[MAX]);

int main()
{
    int anzahl, rueck = 0;

    do
    {
        printf("Laenge der 0/1-Folge (max. 999):");
        rueck = scanf("%3d", &anzahl);
        fflush(stdin);
    }
    while(rueck != 1 || anzahl <1);

    int folge[anzahl];

    for(int i = 0; i <= anzahl; i++)
    {
        folge[i] = 0;
    }
    folge[anzahl] = ziehen(anzahl, folge);

    drucken(anzahl, folge);

    komprimieren(anzahl, folge);
}


int ziehen(int menge, int mat[menge])
{
    for(int j = 0; j <= menge; j++)
    {
        mat[j] = rand() % 2;
    }
    return mat[menge];
}


void drucken(int menge, int mat[menge])
{
    for(int i = 0; i < menge; i++)
    {
        printf("%d ", mat[i]);
    }
    printf("\n");
}


void komprimieren(int menge, int mat[menge])
{
    int mengeN = menge/2 +1;
    int matB[mengeN];

    for(int i = 0; i <= mengeN; i++)
    {
       matB[i] = vergleich(mat);
    }


    drucken(mengeN, matB);
}


