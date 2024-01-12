/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-09 12:00:00 +0100 (Fr, 9. Apr 2021) $
*/


// Hier Code einfügen:

#pragma once
#include "Vektor.h"
#include <iostream>
#include <string>
#include <sstream>


class Koerper : public Vektor
{
public:
	Koerper();																	//Defaultkonstruktor
	Koerper(float Masse0, Vektor Position0, Vektor Geschwindigkeit0);			//Konstruktor für Körper
	Vektor liefereGeschwindigkeit() const;
	float liefereMasse() const ;
	Vektor lieferePosition() const;
	void bewegen(Vektor beschleunigung, float dt);

private:
	Vektor Position;
	Vektor Geschwindigkeit;
	float Masse;
};