#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    unsigned long zahl1 = 0, zahl2 = 0, ergebnis = 0;
    char *zgr1, *zgr2, stringh[80];
    int falsch = 0;

    if(argc != 4)                                       //Erklaerung der Eingabe bei nicht korrekt erfolgter Eingabe
    {
        printf("Richtiger Aufruf: dualrech <operand> <operator> <operand>\n");
        printf("Erlaubte Operatoren sind: +, -, *, /, &, ^\n");
        falsch = 1;
    }

    else
    {
        zahl1 = strtoul(argv[1], &zgr1, 2);             //Umwandeln der strings in Dualzahlen
        zahl2 = strtoul(argv[3], &zgr2, 2);

        if(strlen(zgr1) > 0)                            //Falls Umwandlung nicht moeglich
        {
            printf("\n%s ist keine erlaubte Dualzahl.", argv[1]);
            falsch = 1;
        }

        if(strlen(zgr2) > 0)
        {
            printf("\n%s ist keine erlaubte Dualzahl.", argv[3]);
            falsch = 1;
        }

        switch(argv[2][0])                              //Ausfuehren der jeweiligen Operation
        {
        case '+':   ergebnis = zahl1 + zahl2;   break;
        case '-':   ergebnis = zahl1 - zahl2;   break;
        case '*':   ergebnis = zahl1 * zahl2;   break;
        case '/':
            if(zahl2 == 0)
            {
                printf("Division durch 0 nicht moeglich!!!");
                exit(1);
            }

            if(zahl2 > zahl1)
            {
                printf("Ergebnis kleiner 0 nicht berechenbar");
                exit(1);
            }
            printf("Keine Berechnung von Nachkommastellen\n");
            ergebnis = zahl1 / zahl2;   break;

        case '&':   ergebnis = zahl1 & zahl2;   break;
        case '^':   ergebnis = zahl1 ^ zahl2;   break;
        default :
            printf("\n%s ist keine gueltige Operation\n", argv[2]);
            printf("Erlaubte Operatoren sind: +, -, *, /, &, ^\n");
            falsch = 1;
            break;
        }
        if(falsch == 0)
        {
            printf("%s %s %s = \n", argv[1], argv[2], argv[3]);
            sprintf(stringh, "%lX", ergebnis);                   //Umwandeln des Ergbnisses in Hexadezimal und kopieren in string
            printf("\t\t");

            for(int i =0; i < strlen(stringh); i++)             //Durchlaufen des Hex-strings
            {
                switch(stringh[i])
                {
                case '0':   printf("0000");     break;            //Ausgabe des jeweiligen Stellenwerts in Binaerzahlen
                case '1':   printf("0001");     break;
                case '2':   printf("0010");     break;
                case '3':   printf("0011");     break;
                case '4':   printf("0100");     break;
                case '5':   printf("0101");     break;
                case '6':   printf("0110");     break;
                case '7':   printf("0111");     break;
                case '8':   printf("1000");     break;
                case '9':   printf("1001");     break;
                case 'A':   printf("1010");     break;
                case 'B':   printf("1011");     break;
                case 'C':   printf("1100");     break;
                case 'D':   printf("1101");     break;
                case 'E':   printf("1110");     break;
                case 'F':   printf("1111");     break;
                }
            }
            printf("\t(0x%lX)\n", ergebnis);                    //Ausgabe in Hex
        }
    }
    return(0);
}
