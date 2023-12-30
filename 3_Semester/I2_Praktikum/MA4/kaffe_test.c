#include <stdio.h>
#include <stdlib.h>
#include "automat.h"


int main()
{
    automat_reset();

    printf("\n2 Euro einwurf");             //6 verschiedene Durchlaeufe zum testen Uebergaengen und Zustaenden
    automat_transition(0, 1, 1);
    printf("\n2 Euro einwurf");
    automat_transition(0, 1, 1);
    printf("\nBecher stellen ");
    automat_transition(1, 0, 0);
    printf("\n");

    printf("\n1 Euro einwurf");
    automat_transition(0, 1, 0);
    printf("\n1 Euro einwurf");
    automat_transition(0, 1, 0);
    printf("\n2 Euro einwurf Becher stellen");
    automat_transition(1, 1, 1);
    printf("\n");

    printf("\n1keine gueltige Muenze");
    automat_transition(0, 0, 1);
    printf("\n1 Euro einwurf");
    automat_transition(0, 1, 0);
    printf("\n2 Euro einwurf");
    automat_transition(0, 1, 1);
    printf("\n1 Euro einwurf");
    automat_transition(0, 1, 0);
    printf("\n1 Euro einwurf");
    automat_transition(0, 1, 0);
    printf("\n1 Euro einwurf Becher stellen");
    automat_transition(1, 1, 0);
    printf("\n");

    printf("\n1 Euro einwurf");
    automat_transition(0, 1, 0);
    printf("\n1 Euro einwurf");
    automat_transition(0, 1, 0);
    printf("\n1 Euro einwurf Becher stellen");
    automat_transition(1, 1, 0);
    printf("\n1 Euro einwurf mit stehendem Becher");
    automat_transition(1, 1, 0);
    printf("\n");

    printf("\n2 Euro einwurf");
    automat_transition(0, 1, 1);
    printf("\n2 Euro einwurf");
    automat_transition(0, 1, 1);
    printf("\n1 Euro einwurf Becher stellen");
    automat_transition(1, 1, 0);
    printf("\n");

    printf("\nkeine gueltige Muenze");
    automat_transition(0, 0, 1);
    printf("\n2 Euro einwurf");
    automat_transition(0, 1, 1);
    printf("\n1 Euro einwurf");
    automat_transition(0, 1, 0);
    printf("\n1 Euro einwurf Becher stellen");
    automat_transition(1, 1, 0);
    printf("\n");

return(0);
}
