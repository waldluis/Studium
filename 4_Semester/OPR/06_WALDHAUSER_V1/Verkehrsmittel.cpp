/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-07-7 9:15:00 +0100 (Fr, 07. Mai 2021) $
*/
#include <iostream>
#include <string>
#include <sstream>
#include "Verkehrsmittel.h"

Verkehrsmittel::Verkehrsmittel(const std::string& n):
	name_(n)
{
	position_ = Vektor();
}

Verkehrsmittel::Verkehrsmittel(const Verkehrsmittel & v):
	name_("Kopie von " + v.name())
{
	position_ = Vektor(v.position());
	std::cout << "Kopiere Verkehrsmittel (" << name() << ")" << std::endl;
}

Verkehrsmittel::~Verkehrsmittel()
{
	std::cout << name() << " geloescht" << std::endl;
}

std::string Verkehrsmittel::text() const
{
	std::stringstream hilf;

	hilf << name() << ": Position=" << position_.text();
	return hilf.str();
}

void Verkehrsmittel::bewegeZu(const Vektor& v)
{
	position_ = v;
}

const std::string& Verkehrsmittel::name() const
{
	return this->name_;
}

const Vektor& Verkehrsmittel::position() const
{
	return this->position_;
}
