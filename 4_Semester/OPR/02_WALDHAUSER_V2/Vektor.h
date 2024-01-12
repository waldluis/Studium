/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-12 14:45:00 +0100 (Mo, 12. Apr 2021) $
*/

// Hier Code einfügen:

#pragma once
#include <iostream>
#include <cmath>


class Vektor
{
public:
	Vektor();									//Default Konstruktor
	Vektor(const float& x, const float& y);
	void mul(const float& faktor);
	void add(const Vektor& v);
	Vektor diff(const Vektor& v) const;
	float betrag() const;
	float X;
	float Y;
};