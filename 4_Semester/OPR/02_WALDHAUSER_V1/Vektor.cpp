/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-09 12:00:00 +0100 (Fr, 9. Apr 2021) $
*/


// Hier Code einfügen:

#include "Vektor.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Vektor::Vektor() :												//Defaultkonstruktor
	X(0),
	Y(0)
{}

Vektor::Vektor(float x, float y) :								//Konstruktor mit eingegebenen Werten
	X(x),
	Y(y)
{}


void Vektor::mul(float reibungmasse)							//Methode zum Berechnen der Beschleunigung
{
	X *= reibungmasse;
	Y *= reibungmasse;
}

void Vektor::add(Vektor gravitiaton)							//Methode zum addieren der neuen Beschleunigung
{
	X += gravitiaton.X;
	Y += gravitiaton.Y;
}

Vektor Vektor::diff(Vektor position0) const							//Berechnung der Differenz von aktueller
{																	//Position zum Startpunkt
	Vektor hilf;

	hilf.X = X - position0.X;
	hilf.Y = Y - position0.Y;

	return hilf;
}

float Vektor::betrag() const										//Berechnung des Betrags des Vektors
{
	return sqrt(X *X  + Y * Y);
}