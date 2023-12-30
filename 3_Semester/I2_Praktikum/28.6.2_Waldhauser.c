#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 10

typedef struct Person
{
    char *name;
    int telnummer;
} Person;

Person **freund = NULL;

int auswahl();
int einlesen();
void ausgabe(int menge);
int  vergl_name(const void *zgr1, const void *zgr2);

int main()
{
    int wahl = 1, anzahl;


    printf("Liste mit Namen und Telefonnummer\n\n");

    while(wahl != 0)
    {
        wahl = auswahl();

        if(wahl == 1)
            anzahl = einlesen();

        if(wahl == 2)
        {
            ausgabe(anzahl);
        }
    }

    return 0;
}

int  auswahl(void)
{
    int  wahl;

    do
    {
        printf("  0    Ende\n"
               "  1    Neue Namen und Telefonnummern einfuegen\n"
               "  2    Ausgabe der Liste\n"
               " Ihre Wahl: ");
        scanf("%d", &wahl);
        getchar();
    }
    while (wahl < 0 || wahl > 4);
    return(wahl);
}

int  einlesen(void)
{
    int  n=0, max_n=0;
    char string[100];

    printf("Ende mit leerem Namen");

    while (1)
    {
        printf("\n----Eingabe der %d.Person----\n", n+1);
        printf("Name:           ");
        fgets(string, 100, stdin);
        string[strlen(string)-1] = '\0'; /* \n am Ende entfernen */
        if (strlen(string) == 0)
            break;
        if (n >= max_n)
        {
            max_n += BLOCK;
            freund = (Person **)realloc(freund, max_n*sizeof(Person *));
            if (freund == NULL)
            {
                printf("......Speicherplatzmangel\n");
                exit(1);
            }
        }
        if ( (freund[n] = (Person *)malloc(sizeof(Person))) == NULL)
        {
            printf("......Speicherplatzmangel\n");
            exit(2);
        }
        if ( (freund[n]->name = (char *)malloc(strlen(string)+1)) == NULL)
        {
            printf("......Speicherplatzmangel\n");
            exit(3);
        }
        strcpy(freund[n]->name, string);


        int rueck = 0;
        do
        {
            printf("Telefonnummer:  ");
            rueck = scanf("%d", &freund[n]->telnummer);
            fflush(stdin);
        }
        while(rueck != 1 || freund[n]->telnummer <= 0);
        n++;
    }
    return(n);
}

void ausgabe(int menge)
{
    printf("Sortiert nach Name:\n\n");
    qsort(freund, menge, sizeof(Person *), &vergl_name);

    for(int i = 0; i < menge; i++)
        printf("%s  (%d)\n", freund[i]->name, freund[i]->telnummer);
}

int  vergl_name(const void *zgr1, const void *zgr2)
{
    Person  **p1 = (Person **)zgr1, **p2 = (Person **)zgr2;
    int    vergl=0;

    if      ( (vergl = strcmp( (*p1)->name, (*p2)->name) ) != 0 ) ;
    return( vergl );
}

