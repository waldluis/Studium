#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 10

typedef struct liste
{
    char name[20];
    struct liste *naechst;
}Person;

void einfuegen(char *string, Person *anfang);
void mischen(Person *anfang[3]);                                    //Mischen mit Argument versehen
void drucken(Person *anfang);

int main()
{
    Person *anfang[3], *ende[3];                                    //Keine globale Variablen mehr
    int rueck = 0, nummer;
    char string[20];

    for(int i = 0; i < 3; i++)
    {
        anfang[i] = (Person*) malloc(sizeof(Person));               //Anlegen von Anfang und Ende fuer 3 Listen
        ende[i] = (Person*) malloc(sizeof(Person));

        if(anfang[i] == NULL || ende[i] == NULL)
        {
            printf("Speicherplatzmangel\n");
            exit(1);
        }
        anfang[i]->naechst = ende[i]->naechst = ende[i];            //Verknuepfen zu Beginn ohne Inhalt
    }

    printf("Ende mit leerem Namen\n");

    while(1)
    {
        printf("Name:           ");                                 //Einlesen des Namens
        fgets(string, 20, stdin);
        string[strlen(string)-1] = '\0';                            //Abschneiden von '\n'
        fflush(stdin);

        if (strlen(string) == 0)                                    //Abbruch falls kein Name eingegeben wurde
            break;

        do
        {
            printf("Welche Liste (1 oder 2?):");                    //Auswahl der Liste
            rueck = scanf("%d", &nummer);
            fflush(stdin);
        }
        while(rueck != 1 || nummer < 1 || nummer > 2);

        einfuegen(string, anfang[nummer-1]);                        //Einhaengen der Namen in die jeweilige Liste
    }

    mischen(anfang);                                                      //Erstellen der dritten Liste

    printf("\n1. Liste:\n");                                        //Ausgabe der jeweiligen Liste
    drucken(anfang[0]);
    printf("\n2. Liste:\n");
    drucken(anfang[1]);
    printf("\nGemischte Liste:\n");
    drucken(anfang[2]);

    return(0);
}

void einfuegen(char *string, Person *anfang)
{
    Person *neu, *zeiger_liste;                                     //Hilfszeiger

    neu = (Person*) malloc(sizeof(Person));
    if(neu == NULL)
    {
        printf("Speicherplatzmangel\n");
            exit(1);
    }

    strcpy(neu->name, string);

    zeiger_liste = anfang;                                          //Setzen des Hilfszeigers auf den Anfang der jeweiligen Liste

    while(zeiger_liste->naechst != zeiger_liste->naechst->naechst)
    {
        if(strcmp(string, zeiger_liste->naechst->name) <= 0)        //Einhaengen der Namen nach Alphabet
            break;

        zeiger_liste = zeiger_liste->naechst;
    }
    neu->naechst = zeiger_liste->naechst;                           //Uebergabe der Zeiger
    zeiger_liste->naechst = neu;
}

void mischen(Person *anfang[3])
{
    Person *zeiger[2];

    zeiger[0] = anfang[0]->naechst;                                 //Hilfszeiger auf den Anfang der zwei Listen
    zeiger[1] = anfang[1]->naechst;

    while(zeiger[0] != zeiger[0]->naechst)                          //Durchlaufen der 1. Liste und alphabetisches einhaengen der Elemente
    {                                                               //in die dritte Liste
        einfuegen(zeiger[0]->name, anfang[2]);
        zeiger[0] = zeiger[0]->naechst;
    }

    while(zeiger[1] != zeiger[1]->naechst)                           //Durchlaufen der 2. Liste und alphabetisches einhaengen der Elemente
    {                                                                //in die dritte Liste
        einfuegen(zeiger[1]->name, anfang[2]);
        zeiger[1] = zeiger[1]->naechst;
    }

}

void drucken(Person *anfang)
{
    Person *zeiger_liste;

    zeiger_liste = anfang->naechst;

    while(zeiger_liste != zeiger_liste->naechst)                    //Durchlauf der jeweiligen Liste und Ausgabe der Elemente bis Listenende
    {
        printf("    %s\n", zeiger_liste->name);
        zeiger_liste = zeiger_liste->naechst;
    }
}

