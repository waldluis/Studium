#include <stdio.h>
#include <stdlib.h>

int main()
{
    int wert;

    //Teilaufgabe 1

    int a=-15;
    wert=-20<=a<100;
    printf("1.Wert: %d\n", wert);

    //Teilaufgabe 2

    int x=1, y=7;
    wert= x<0 && 5<=y && y<=30;
    printf("2.Wert: %d\n", wert);

   //Teilaufgabe 3

    int z=15;
    wert= (z%2) && (z%3==0) && (z%5==0);
   printf("3.Wert: %d\n", wert);

   //Teilaufgabe 4

   int jahr=2100;
   wert= jahr%400 && (jahr%4 && jahr%100);
   printf("4.Wert: %d\n", wert);

   //Teilaufgabe 5

   a=25;
   int b=10;
   unsigned char charVar;
   charVar= a*b;
   wert= 250 == charVar;            //da Wertebereich von unsigned char bis 255 geht
   printf("5.Wert: %d\n", wert);

   //Teilaufgabe 6

   char antwort= 'A';
   wert= antwort=='j' && antwort=='J';
   printf("6.Wert: %d\n", wert);


   //Teilaufgabe 7

   int zaehler=30;
   wert= (5<=zaehler && zaehler<=25) !=1;
   printf("7.Wert: %d\n", wert);

    return 0;
}
