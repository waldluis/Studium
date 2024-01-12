/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-07-7 9:15:00 +0100 (Fr, 07. Mai 2021) $
*/

#include <iostream>
#include <string>
#include <sstream>
#include "Radfahrzeug.h"

Radfahrzeug::Radfahrzeug(const std::string& name, int i) :
	anzahlRaeder_(i),
	Verkehrsmittel(name)
{}

Radfahrzeug::Radfahrzeug(const Radfahrzeug& r) :
	Verkehrsmittel(r),
	anzahlRaeder_(r.anzahlRaeder())
{
	std::cout << "Kopiere Radfahrzeug" << std::endl;
}

int Radfahrzeug::anzahlRaeder() const
{
	return anzahlRaeder_;;
}

std::string Radfahrzeug::text() const
{
	std::stringstream hilf;
	
	hilf << Verkehrsmittel::text() << " Raeder=" << anzahlRaeder();
	return hilf.str();
}