#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159                                         //Definition Pi

int main()
{
    char wahl;

    printf("Was moechten Sie berechnen? \n"
          "Quadrat: q \n"
          "Rechteck: r \n"
          "Kreis: k \n"
          "Ellipse: e \n \n"
          "Ihre Wahl:");

    scanf("%c", &wahl);

    double a;
    double b;
    double flaeche=0;

    switch (wahl){

        case 'q':                                           //Quadrat
            printf("\nBitte die Seitenlaenge eingeben:");
            scanf("%lf", &a);
            flaeche= a*a;
            printf("\nFlaeche des Quadrats = %.2l f", flaeche);
            break;

        case 'r':                                           //Rechteck
            printf("\nSeitenlaenge der 1. Seite");
            scanf("%lf", &a);
            printf("\nSeitenlaenge der 2. Seite");
            scanf("%lf", &b);
            flaeche= a*b;
            printf("\nFlaeche des Rechtecks = %.2lf", flaeche);
            break;

        case 'k':                                           //Kreis
            printf("\nBitte den Radius eingeben:");
            scanf("%lf", &a);
            flaeche= a*a*PI;
            printf("\nFlaeche des Kreises = %.2lf", flaeche);
            break;

        case 'e':                                           //Ellipse
            printf("\nRadius der x-Achse:");
            scanf("%lf", &a);
            printf("\nRadius der y-Achse:");
            scanf("%lf", &b);
            flaeche= a*b*PI;
            printf("\nFlaeche des Quadrats = %.2lf", flaeche);
            break;

        default:
            printf("\n%c ist keine gueltige Eingabe", wahl);

    }

    return 0;
}
