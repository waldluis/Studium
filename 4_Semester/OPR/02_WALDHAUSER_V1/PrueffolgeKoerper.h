/**
* $Author: MahrTh $
* $Rev: 118 $
* $Date: 2015-03-21 21:39:51 +0100 (Sa, 21. Mär 2015) $
*
* ACHTUNG: Diese Datei darf nicht verändert werden!
*/
#pragma once
#include "Prueffolge.h"

class PrueffolgeKoerper : public Prueffolge
{
public:

	PrueffolgeKoerper();

private:

	static void pruefungKinematik();
};

