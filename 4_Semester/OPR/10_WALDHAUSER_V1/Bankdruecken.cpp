/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-11 11:30:00 +0100 (FR, 11. Juni 2021) $
*/

#include "Bankdruecken.h"
#include "Sportler.h"

Bankdruecken::Bankdruecken():
	_eingestelltesGewicht(0)
{}

int Bankdruecken::eingestelltesGewicht() const
{
	return _eingestelltesGewicht;
}

Bankdruecken& Bankdruecken::gewichtEinstellen(int gewicht)
{
	_eingestelltesGewicht = gewicht;
	return *this;
}

double Bankdruecken::energieProWiederholung(const Sportler& sportler)
{
	return ERDBESCHLEUNIGUNG * eingestelltesGewicht() * sportler.armlaenge();
}

std::ostream& operator<<(std::ostream& os, const Bankdruecken& geraet)
{
	os << "Auf dem Geraet Bankdruecken sind " << geraet.eingestelltesGewicht() << " kg eingestellt.";
	return os;
}
