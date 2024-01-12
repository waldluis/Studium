/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-12 14:45:00 +0100 (Mo, 12. Apr 2021) $
*/

#pragma once
#include "Vektor.h"
#include <sstream>


class Koerper : public Vektor
{
public:
	Koerper();																	//Defaultkonstruktor
	Koerper(const float& Masse0, const Vektor& Position0, const Vektor& Geschwindigkeit0);			//Konstruktor für Körper
	Vektor liefereGeschwindigkeit() const;
	float liefereMasse() const ;
	Vektor lieferePosition() const;
	void bewegen(Vektor& v, const float& dt);

private:
	Vektor Position;
	Vektor Geschwindigkeit;
	float Masse;
};