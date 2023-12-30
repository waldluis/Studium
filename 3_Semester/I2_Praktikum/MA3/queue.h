/**********************************************************************\
* Kurzbeschreibung:
* queue.h - realisiert eine Queue (Warteschlange) als verkettete Liste
*
* Datum:     Autor:
* 30.9.2015  Prof. Dr. Helmut Herold
*
\**********************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

/*--- #includes ------------------------------------------------------*/
#include <limits.h>

/*--- #defines -------------------------------------------------------*/
#define TRUE  1
#define FALSE 0
#define QLEER INT_MIN

/*--- Datentypen (typedef) -------------------------------------------*/
typedef int Bool;

/*--- Prototypen globaler Funktionen ---------------------------------*/

/*--------------------------------------------------------------------*\
 * Einfuegen in Liste
 * Parameter:
 *    zahl  fügt die übergebene Zahl 'zahl' am Ende der Liste ein
 * Return Wert:
 *    TRUE  wenn noch genug Speicherplatz vorhanden
 *    FALSE wenn kein Speicherplatz mehr allokiert werden konnte
 * Hinweis:
 * - dynamische Verwaltung von Speicher muss mit malloc() und free()
 *   durchgeführt werden; dynamische Arrays sind nicht erlaubt !!!
 *--------------------------------------------------------------------*/
Bool put(int zahl);

/*--------------------------------------------------------------------*\
 * Auslesen aus Liste
 * Parameter:
 *    keine
 * Return Wert:
 *    Zahl am Anfang der Liste oder aber QLEER, wenn Liste leer ist.
 *--------------------------------------------------------------------*/
int get(void);

/*--------------------------------------------------------------------*\
 * Pruefen der Liste
 * Parameter:
 *    keine
 * Return Wert:
 *    liefert TRUE, wenn Queue leer ist, sonst FALSE
 *--------------------------------------------------------------------*/
Bool isEmpty(void);

void queue_init();

#endif /*QUEUE_H*/

