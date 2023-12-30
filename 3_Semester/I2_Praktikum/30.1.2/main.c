#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE *text;
    int c, zeile = 1;

    if(argc != 2)                                                       //Abbruch bei falscher Zahl an Argumenten
    {
        printf("Richtiger Aufruf: numausg <datei.txt> \n");
        exit(1);
    }

    text = fopen(argv[1], "r");                                         //Oeffnen der Datei

    if(text == NULL)
    {
        printf("Fehler beim oeffnen der Datei %s...", argv[1]);         //Abbruch falls oeffnen nicht moeglich
        return(1);
    }

    printf("%d  ", zeile);                                              //Erste Zeilennummer
    while(1)
    {
        c = fgetc(text);                                                //Zeichenweiﬂe durch den Text laufen

        if(c == EOF)                                                    //Ende wenn EOF
            break;

        if(c == '\n')
        {
            zeile++;                                                    //Zeilennummer hochzaehlen wenn Umbruch
            printf("%c", c);
            printf("%d  ", zeile);
        }
        else printf("%c", c);
    }
    fclose(text);
    return(0);
}
