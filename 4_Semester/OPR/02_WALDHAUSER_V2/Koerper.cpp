/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-12 14:45:00 +0100 (Mo, 12. Apr 2021) $
*/


// Hier Code einfügen:

#include "Koerper.h"
#include <sstream>
using namespace std;

Koerper::Koerper() :																	//Initialisierung mit allen Werten 0
	Position(0, 0),
	Geschwindigkeit(0, 0),
	Masse(0)
{}

Koerper::Koerper(const float& Masse0, const Vektor& Position0, const Vektor& Geschwindigkeit0) :				//Initialsierung mit eingegebenen Werten
	Position(Position0),
	Geschwindigkeit(Geschwindigkeit0),
	Masse(Masse0)
{}

void Koerper::bewegen(Vektor& v, const float& dt)					//Berechnen der aktuellen Position und Geschwindigkeit mit Vektormethoden
{					
	v.mul(dt);
	Geschwindigkeit.add(v);

	Vektor hilf = Geschwindigkeit;									//Hilfsvektor da Geschwindigkeit nicht mehr verändert werden darf

	hilf.mul(dt);
	Position.add(hilf);
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