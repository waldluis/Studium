#include <stdio.h>
#include <stdlib.h>

int main()
{
   int kandidat[4];
   int stimmen;
   double anteil[4];

   printf("Stimmen fuer den 1. Kandidaten:");
   scanf("%d", &kandidat[0]);
   printf("Stimmen fuer den 2. Kandidaten:");
   scanf("%d", &kandidat[1]);
   printf("Stimmen fuer den 3. Kandidaten:");
   scanf("%d", &kandidat[2]);
   printf("Stimmen fuer den 4. Kandidaten:");
   scanf("%d", &kandidat[3]);

   stimmen= kandidat[0]+kandidat[1]+kandidat[2]+kandidat[3];
   printf("\nAnzahl aller Stimmen: %d \n\n", stimmen);

   anteil[0]= ((double)kandidat[0]/stimmen)*100;
   anteil[1]= ((double)kandidat[1]/stimmen)*100;
   anteil[2]= ((double)kandidat[2]/stimmen)*100;
   anteil[3]= ((double)kandidat[3]/stimmen)*100;

   printf("1. Kandidat: %.2f %% \n", anteil[0]);
   printf("2. Kandidat: %.2f %% \n", anteil[1]);
   printf("3. Kandidat: %.2f %% \n", anteil[2]);
   printf("4. Kandidat: %.2f %% \n", anteil[3]);

    return 0;
}
