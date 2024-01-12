/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-07-7 9:15:00 +0100 (Fr, 07. Mai 2021) $
*/
// Pkw.h, Vektor.h und Heissluftballon.h in einer Datei um Dateianzahl zu verringern


#pragma once
#include <iostream>
#include <string>
#include <sstream>

class Vektor
{
public:
	int x;
	int y;
	Vektor() : x(0), y(0) {};

	Vektor(int a, int b) : x(a), y(b) {};

	std::string text() const
	{
		std::stringstream hilf;

		hilf << "(" << x << "," << y << ")";
		return hilf.str();
	};
};
