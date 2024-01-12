/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-11 11:30:00 +0100 (FR, 11. Juni 2021) $
*/

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Sportler.h"

class EnergieFormatJoule;
class EnergieFormatSchokolade;

template<typename T>
class Uebung
{
private:
	Sportler* _sportler;
	Bankdruecken* _geraet;
	int _anzahlSaetze;
	int _anzahlWiederholungen;
	double _energieUmsatz;
	T _einheit;

public:
	Uebung(Sportler& sportler, Bankdruecken& geraet, int anzahlSaetze, int anzahleWiederholungen, double gewicht);
	void ausfuehren(std::stringstream& s);
	void ausfuehren(std::ostream& os);
	std::string energieUmsatz() const;
};


template<typename T>
inline Uebung<T>::Uebung(Sportler& sportler, Bankdruecken& geraet, int anzahlSaetze, int anzahleWiederholungen, double gewicht):
	_anzahlSaetze(anzahlSaetze), _anzahlWiederholungen(anzahleWiederholungen), _energieUmsatz(0)
{
	geraet.gewichtEinstellen(gewicht);
	_geraet = &geraet;
	_sportler = &sportler;
}

template<typename T>
inline void Uebung<T>::ausfuehren(std::stringstream& s)
{
	for (int i = 0; i < _anzahlSaetze * _anzahlWiederholungen; i++)
	{
		_energieUmsatz += (_sportler->wiederholungAusfuehren(*_geraet));
	}

	s << _sportler->name() << " hat beim Bankdruecken in " << _anzahlSaetze << " Saetzen mit jeweils " << _anzahlWiederholungen << " Wiederholungen und " <<
		_geraet->eingestelltesGewicht() << "kg Gewicht " << energieUmsatz() << "  an Energie umgesetzt.\n";
}

template<class T>
inline void Uebung<T>::ausfuehren(std::ostream& os)
{
	std::stringstream s;
	ausfuehren(s);
	os << s.str();
}

template<typename T>
inline std::string Uebung<T>::energieUmsatz() const
{
	std::string hilf, hilf2;

	if (_einheit._faktor == 1000)
	{
		hilf = std::to_string(_sportler->energieUmsatz() / _einheit._faktor);				// Formatierung auf 2 Nachkommastellen
		hilf2 = hilf.substr(0, hilf.find(".") + 3);
		hilf2 +=" kJ";
	}
	else 
	{
		hilf = std::to_string(_sportler->energieUmsatz() / _einheit._faktor);				// Formatierung auf 3 Nachkommastellen
		hilf2 = hilf.substr(0, hilf.find(".") + 4);
		hilf2 += " Tafeln Schokolade"; 
	}
	return hilf2;
}
