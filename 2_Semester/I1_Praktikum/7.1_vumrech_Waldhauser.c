#include <stdio.h>
#include <stdlib.h>
#include "faktor.h"


int main()
{
    double S;
    double M;
    double MS;
    double KMH;
    double KMTAG;
    double MTAG;

    printf("Bitte Strecke in Meter eingeben:");
    scanf("%lf", &M);
    printf("Bitte benoetigte Zeit dafuer eingeben (in Sekunden):");
    scanf("%lf", &S);

    MS= M/S;
    KMH= MS * MS_nach_KMH;
    KMTAG= MS * MS_nach_KMTAG;
    MTAG= MS * MS_nach_MTAG;
    printf("Entspricht folgender Geschwindigkeit: \n%lf m/s \n", MS);
    printf("%lf km/h \n", KMH);
    printf("%lf m/tag \n", MTAG);
    printf("entspricht: %lf km/tag \n", KMTAG);

    return 0;
}
