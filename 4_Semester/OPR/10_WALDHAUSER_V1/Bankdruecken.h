/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-11 11:30:00 +0100 (FR, 11. Juni 2021) $
*/

#pragma once
#include <iostream>

class Sportler;

class Bankdruecken
{
private:
	int _eingestelltesGewicht;
	
public:
	constexpr static double ERDBESCHLEUNIGUNG = 9.81;
	Bankdruecken();
	int eingestelltesGewicht() const;
	Bankdruecken& gewichtEinstellen(int gewicht);
	double energieProWiederholung(const Sportler& sportler);
	friend std::ostream& operator<<(std::ostream& os, const Bankdruecken& geraet);
};
