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
#include "Luftfahrzeug.h"

using namespace std;

class Heissluftballon : public Luftfahrzeug
{
private:
	int ballonVolumen_;

public:
	Heissluftballon(const std::string& name, int hoehe, int volumen) :
		ballonVolumen_(volumen), Luftfahrzeug(name, hoehe) {};

	int ballonVolumen() const { return ballonVolumen_; };

	std::string text() const
	{
		std::stringstream hilf;
		
		hilf << Luftfahrzeug::text() << ", ballonVolumen=" << ballonVolumen() << "m^3";
		return hilf.str();
	};
};