/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-12 14:45:00 +0100 (Mo, 12. Apr 2021) $
*/


// Hier Code einfügen:

#include "Vektor.h"
#include <iostream>
#include <cmath>
using namespace std;

Vektor::Vektor() :												//Defaultkonstruktor
	X(0),
	Y(0)
{}

Vektor::Vektor(const float& x, const float& y) :								//Konstruktor mit eingegebenen Werten
	X(x),
	Y(y)
{}


void Vektor::mul(const float& faktor)							//Methode zum Berechnen der Beschleunigung
{
	X *= faktor;
	Y *= faktor;
}

void Vektor::add(const Vektor& v)							//Methode zum addieren der neuen Beschleunigung
{
	X += v.X;
	Y += v.Y;
}

Vektor Vektor::diff(const Vektor& v) const							//Berechnung der Differenz von aktueller
{																	//Position zum Startpunkt
	Vektor hilf;
	
	hilf.X = X - v.X;
	hilf.Y = Y - v.Y;

	return hilf;
}

float Vektor::betrag() const										//Berechnung des Betrags des Vektors
{
	return sqrt(X * X  + Y * Y);
}