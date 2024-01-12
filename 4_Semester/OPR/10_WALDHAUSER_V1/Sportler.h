/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-11 11:30:00 +0100 (FR, 11. Juni 2021) $
*/

#pragma once
#include <string>
#include <iostream>

class ostream;
class Bankdruecken;

class Sportler
{
private:
	std::string _name;
	int _koerpergewicht;
	double _armlaenge;
	double _energieUmsatz;

public:
	constexpr static double WIRKUNGSGRAD = 0.25;
	Sportler(std::string name, int koerpergewicht, double armlaenge);
	std::string name() const;
	int koerpergewicht() const;
	double armlaenge() const;
	double energieUmsatz() const;
	friend std::ostream& operator<<(std::ostream& os, const Sportler& sportler);
	double wiederholungAusfuehren(Bankdruecken& geraet);
};
