/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-09 12:00:00 +0100 (Fr, 9. Apr 2021) $
*/


// Hier Code einfügen:

#include "Koerper.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Koerper::Koerper() :																	//Initialisierung mit allen Werten 0
	Position(0, 0),
	Geschwindigkeit(0, 0),
	Masse(0)
{}

Koerper::Koerper(float Masse0, Vektor Position0, Vektor Geschwindigkeit0) :				//Initialsierung mit eingegebenen Werten
	Position(Position0),
	Geschwindigkeit(Geschwindigkeit0),
	Masse(Masse0)
{}

void Koerper::bewegen(Vektor beschleunigung, float dt)					//Berechnen der aktuellen Position und Geschwindigkeit
{
	Geschwindigkeit.X += dt * beschleunigung.X;
	Geschwindigkeit.Y += dt * beschleunigung.Y;

	Position.X += dt * Geschwindigkeit.X;
	Position.Y += dt * Geschwindigkeit.Y;
}

Vektor Koerper::liefereGeschwindigkeit() const
{
	return Geschwindigkeit;
}

float Koerper::liefereMasse() const
{
	return Masse;
}

Vektor Koerper::lieferePosition() const
{
	return Position;
}