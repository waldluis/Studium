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
#include "Radfahrzeug.h"

class Pkw : public Radfahrzeug
{
private:
	int anzahlTueren_;

public:
	Pkw(const std::string n, int i) : anzahlTueren_(i), Radfahrzeug(n, 4) {};

	Pkw(const Pkw& p) : anzahlTueren_(p.anzahlTueren_), Radfahrzeug(p)
	{ std::cout << "Kopiere Pkw" << std::endl; };

	int anzahlTueren() const { return anzahlTueren_; };

	std::string text() const
	{
		std::stringstream hilf;

		hilf << Radfahrzeug::text() << " Tueren=" << anzahlTueren();
		return hilf.str();
	};
};
