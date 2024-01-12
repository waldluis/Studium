/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-09 12:00:00 +0100 (Fr, 9. Apr 2021) $
*/

// Hier Code einfügen:

#pragma once
#include <iostream>
#include <string>
#include <sstream>


class Vektor
{
public:
	Vektor();									//Default Konstruktor
	Vektor(float x, float y);
	void mul(float reibungmasse);
	void add(Vektor gravitation);
	Vektor diff(Vektor position0) const;
	float betrag() const;
	float X;
	float Y;
};