/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-11 11:30:00 +0100 (FR, 11. Juni 2021) $
*/

#include "Sportler.h"
#include "Bankdruecken.h"

Sportler::Sportler(std::string name, int koerpergewicht, double armlaenge):
	_name(name),
	_koerpergewicht(koerpergewicht),
	_armlaenge(armlaenge),
	_energieUmsatz(0)
{}

std::string Sportler::name() const
{
	return _name;
}

int Sportler::koerpergewicht() const
{
	return _koerpergewicht;
}

double Sportler::armlaenge() const
{
	return _armlaenge;
}

double Sportler::energieUmsatz() const
{
	return _energieUmsatz;
}

double Sportler::wiederholungAusfuehren(Bankdruecken& geraet)
{
	_energieUmsatz += geraet.energieProWiederholung(*this) / Sportler::WIRKUNGSGRAD;
	return _energieUmsatz;
}

std::ostream& operator<<(std::ostream& os, const Sportler& sportler)
{
	os << sportler.name() << ": Koerpergewicht = " << sportler.koerpergewicht() << " kg, Armlaenge = " << sportler.armlaenge() << " m, Energieumsatz = " << sportler.energieUmsatz() << " J";
	return os;
}
