#include <stdio.h>
#include <stdlib.h>

int main()
{
   int okt;
   int check;
   printf("Bitte eine Oktalzahl eingeben: ");
   check= scanf("%o", &okt);
   printf("Eingabe richtig, wenn hier '1' steht: %d\n", check);
   printf("-->%o (8) = %d (10) = %X (16)", okt, okt, okt);
   return(0);
}
