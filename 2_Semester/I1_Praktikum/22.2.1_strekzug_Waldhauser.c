#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char jaNein();
double strecken_laenge(double x0, double y0, double xNeu, double yNeu);

int main()
{
    double x0, y0, rueck =0;
    double xNeu, yNeu;
    double strecke = 0;
    int fehler = 0;
    char c;
    char antwortja;

    printf("Programm zum Berechnen einer Strecke im Koordinatensystem \n\n\n");


    do
    {
        printf("Bitte Startpunkt eingeben (x,y):");
        rueck = scanf("%lf,%lf", &x0, &y0);

        while((c = getchar()) != '\n' && c != EOF)
        {
            fehler++;
        }

        if (fehler != 0 || rueck != 2)
        {
            printf("Eingabe falsch bitte Wiederholen");
        }
        else
        {
            printf("Startkoordinaten sind (%.2lf / %.2lf). Korrekt? (j/n)", x0, y0);
            antwortja = jaNein();
        }
        fehler = 0;
        rueck = 0;
    }
    while(antwortja != 'j' && antwortja != 'J');
    antwortja = 0;

    do
    {
        do
        {
            rueck = 0;
            fehler = 0;
            printf("Weiterer Streckenpunkt (x,y):");
            fflush(stdin);
            rueck = scanf("%lf,%lf", &xNeu, &yNeu);

            while((c = getchar()) != '\n' && c != EOF)
            {
                fehler++;
            }

            if (fehler != 0 || rueck != 2)
            {
                printf("Eingabe falsch bitte Wiederholen. \n");
            }
            else
            {
                printf("Streckenpunkt ist (%.2lf / %.2lf). Korrekt? (j/n)", xNeu, yNeu);
                antwortja = jaNein();
            }

            fehler = 0;
            rueck = 0;
        }
        while(antwortja != 'j' && antwortja != 'J');
        rueck = 0;

        strecke += strecken_laenge(x0, y0, xNeu, yNeu);
        x0 = xNeu;
        y0 = yNeu;

        printf("Noch ein Streckenpunkt? (j/n)");
        antwortja = 0;
        antwortja = jaNein();


    }
    while(antwortja == 'j' || antwortja == 'J');

    printf("\nDie Laenge der Strecke betraegt %.2lf Einheiten.", strecke);

    return 0;
}


char jaNein()
{
    int fehler = 0;
    char ja = 0, c = 0;

    do
    {
        ja = 0;
        fflush(stdin);
        scanf("%c", &ja);
        while ((c = getchar()) != '\n' && c != EOF)
        {
            fehler++;
        }

        if (fehler == 0 && (ja == 'j' || ja ==  'J'))
        {
            printf("Sie haben 'ja' gewaehlt. \n\n");
        }
        else if (fehler == 0 && (ja == 'n' || ja == 'N'))
        {
            printf("Sie haben 'nein' gewaehlt. \n\n");
        }
        else
        {
            printf("Eingabe falsch bitte j/J oder n/N eingeben. \n");
            fehler = 0;
            ja = 0;
        }
    }
    while(ja == 0);
    return ja;
}

double strecken_laenge(double x0, double y0, double xNeu, double yNeu)
{
    double laenge;
    double deltaX, deltaY;

    deltaX = xNeu - x0;
    deltaY = yNeu - y0;
    laenge = sqrt(pow(deltaX, 2.0) + pow(deltaY, 2.0));

    printf("In diesem Schritt hat der Zug %.2lf LE zurückgelegt.\n", laenge);
    return laenge;

}
