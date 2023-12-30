/**********************************************************************\
* Kurzbeschreibung:
* queue.c - realisiert eine Queue (Warteschlange)
*
* Datum:     Autor:
*
*
\**********************************************************************/

/*--- #includes ------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*--- #defines -------------------------------------------------------*/

/*--- Lokale Datentypen (typedef) ------------------------------------*/
typedef struct liste
{
    int zahl;
    struct liste *nach;
} Element;

/*--- Modulglobale static Variablen ----------------------------------*/
Element *anfang;

/*--- Prototypen lokaler Funktionen ----------------------------------*/

/*--- Funktionsdefinitionen ------------------------------------------*/

/*Funktion zum initialisieren der queue*/
void queue_init()
{
    anfang = (Element*)malloc(sizeof(Element));

    if(anfang == NULL)
    {
        printf("Kein Speicherplatz vorhanden");
        exit(0);
    }
    else
    {
        anfang->zahl = 0;                       //Nullsetzen der Werte da anfang nicht ausgegeben wird
        anfang->nach = NULL;
    }
}

/*--------------------------------------------------------------------*\
 * Einfuegen in Liste
 * Parameter:
 *    zahl  fügt die übergebene Zahl 'zahl' am Ende der Liste ein
 * Return Wert:
 *    TRUE  wenn noch genug Speicherplatz vorhanden
 *    FALSE wenn kein Speicherplatz mehr allokiert werden konnte
 *--------------------------------------------------------------------*/
Bool put(int zahl)
{
    Bool wert;

    Element *zeiger, *neu;

    neu = (Element*) malloc(sizeof(Element));

    if(neu == NULL)
    {
        wert = FALSE;
        return(wert);
    }
    else
    {
        if(isEmpty() == TRUE)                   //Falls die queue noch keine Elemente hat
        {
            anfang->nach = neu;
            neu->nach = NULL;
            neu->zahl = zahl;
        }
        else                                    //Falls Elemente in der queue sind
        {
            zeiger = anfang;
            while(zeiger->nach != NULL)         //Ende der queue suchen
                zeiger = zeiger->nach;

            zeiger->nach = neu;                 //Anhaengen der Zahl mit Pointeruebergabe
            neu->nach = NULL;
            neu->zahl = zahl;
        }

        wert = TRUE;
        return(wert);
    }
}

/*--------------------------------------------------------------------*\
 * Auslesen aus Liste
 * Parameter:
 *    keine
 * Return Wert:
 *    Zahl am Anfang der Liste oder aber QLEER, wenn Liste leer ist.
 *--------------------------------------------------------------------*/
int get(void)
{
    int wert;
    Element *zeiger;

    if(isEmpty() == FALSE)
    {
        zeiger = anfang->nach;                      //Aushaengen des ersten Elements
        anfang->nach = zeiger->nach;
        wert = zeiger->zahl;
        free(zeiger);                               //Freigabe des Speichers
    }
    else wert = QLEER;

    return(wert);
}

/*--------------------------------------------------------------------*\
 * Pruefen der Liste
 * Parameter:
 *    keine
 * Return Wert:
 *    liefert TRUE, wenn Queue leer ist, sonst FALSE
 *--------------------------------------------------------------------*/
Bool isEmpty(void)
{
    Bool wert;

    if(anfang->nach == NULL)
        wert = TRUE;

    else wert = FALSE;

    return(wert);
}
