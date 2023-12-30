/**********************************************************************\
 * Kurzbeschreibung: automat.h
 * Stellt Funktionen zur Realisierung eines Automaten zur Verfügung,  
 * die über die in der automat.h vorgegebene C-Schnittstelle 
 * mit einer grafischen Schnittstelle kommunizieren. 
 *
 * Datum:       Autor:        Grund der Aenderung:
 * 
 *
\**********************************************************************/
#ifndef AUTOMAT_H
#define AUTOMAT_H

/*--- #defines -------------------------------------------------------*/
#define true  1
#define false 0
/*--- Datentypen (typedef) -------------------------------------------*/
typedef int BOOL;

typedef struct {
    BOOL display;
    BOOL muenz_rueck;
    BOOL kaffee_los;
    int  guthaben;
    const char * display_string;
} fsm_action_t;

/*--- Prototypen globaler Funktionen ---------------------------------*/
/*--------------------------------------------------------------------*
 * Setzt den Automat in IDLE state                                    *
 *--------------------------------------------------------------------*/
extern void automat_reset(void);

/*--------------------------------------------------------------------*
 * Fuehrt Zustandsuebergaenge durch                                   *
 *--------------------------------------------------------------------*/
extern void automat_transition(BOOL becher, BOOL muenze, BOOL muenz_wert);

/*--------------------------------------------------------------------*
 * Gibt Informationen ueber aktuellen Zustand zurueck                 *
 *--------------------------------------------------------------------*/
extern fsm_action_t automat_output(void);

#endif /* AUTOMAT_H */
