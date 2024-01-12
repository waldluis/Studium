/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-07-7 9:15:00 +0100 (Fr, 07. Mai 2021) $
*/

#include <iostream>
#include <string>
#include <sstream>
#include "Luftfahrzeug.h"

Luftfahrzeug::Luftfahrzeug(const std::string& name, int hoehe) :
	maxFlughoehe_(hoehe),
	Verkehrsmittel(name)
{}

Luftfahrzeug::Luftfahrzeug(const Luftfahrzeug& l) :
	Verkehrsmittel(l),
	maxFlughoehe_(l.maxFlughoehe_)
{
	std::cout << "Kopiere Luftfahrzeug" << std::endl;
}

int Luftfahrzeug::maxFlughoehe() const
{
	return maxFlughoehe_;
}

std::string Luftfahrzeug::text() const
{
	std::stringstream hilf;

	hilf << Verkehrsmittel::text() << ", maxFlughoehe=" << maxFlughoehe() << "m";
	return hilf.str();
}
