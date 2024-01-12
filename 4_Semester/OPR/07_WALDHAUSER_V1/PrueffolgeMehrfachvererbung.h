/**
* $Author: $
* $Rev: $
* $Date: $
* ACHTUNG: Diese Datei darf nicht verändert werden!
*/
#pragma once
#include "Prueffolge.h"

class PrueffolgeMehrfachvererbung : public Prueffolge
{
public:
	PrueffolgeMehrfachvererbung();
private:
	static void pruefungA();
	static void pruefungB();
	static void pruefungC();
	static void pruefungD();
	static void pruefungAnzahlObjekte();
	static void pruefungObjektgroesse();
	static void pruefungVererbung();
};
