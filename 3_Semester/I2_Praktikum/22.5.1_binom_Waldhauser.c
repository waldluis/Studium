#include <stdio.h>
#include <stdlib.h>

int binom(int a, int b)
{
    int c;

    if(a == b || b == 0)
    {
        c = 1;                                                  //Wert für k = 0 oder k = n
    }
    else
    {
        c = binom(a-1, b) + binom(a-1, b-1);                    //Berechnung des Binomialkoeffizienten
    }

    return c;
}

int main()
{
    int n = 0, k = 0, erg;
    char c;

    while (n <= 0)
    {
        printf("Wie viele Positionen?");
        scanf("%d", &n);
        while((c = getchar()) != '\n' && c != EOF ) {}          //Benutzereingabe mit Überprüfung
        fflush(stdin);
    }

    do
    {
        printf("Wie viele Elemente (muss <= %d sein):", n);     //Benutzereingabe mit Überprüfung
        scanf("%d", &k);
        while((c = getchar()) != '\n' && c != EOF ) {}
        fflush(stdin);
    }
    while (k <= 0 || k >= n);

    erg = binom(n, k);

    printf("  / %d \\ \n", n);
    printf(" |     |  = %d \n", erg);                      //Ausgabe des Ergbnisses
    printf("  \\ %d / \n", k);
    return 0;
}


