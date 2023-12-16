#include <stdio.h>
#include <stdlib.h>

int main()
{
   int zeit;

   printf("Bitte die Stunde der aktuelle Uhrzeit eingeben:");
   scanf("%d", &zeit);

   if(zeit>=24)
   {    printf("---> %d ist keine gueltige Stunde", zeit);}

   else if(zeit==23 || zeit>=0 && zeit<=5)
   {    printf("---> Gute Nacht");}

   else if(zeit>=6 && zeit<=10)
   {    printf("---> Guten Morgen");}

    else if(zeit>=11 && zeit<=13)
   {    printf("---> Mahlzeit");}

   else if(zeit>=14 && zeit<=17)
   {    printf("---> Schoenen Nachmittag");}

   else {printf("---> Guten Abend");}

    return 0;
}
