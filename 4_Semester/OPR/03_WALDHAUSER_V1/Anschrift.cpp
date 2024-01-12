/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-16 14:00:00 +0100 (Fr, 16. Apr 2021) $
*/

#include "Anschrift.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Anschrift::Anschrift() :								//Defaultkonstruktor
	_strasse("unbekannte Strasse"),
	_hausnummer("unbekannte Hausnummer"),
	_postleitzahl(0),
	_stadt("unbekannte Stadt")
{}

Anschrift::Anschrift(const string& strasse, const string& hausnummer, int postleitzahl, const string& stadt) :		//Konstruktor mit gegebenen Werten
	_strasse(strasse),
	_hausnummer(hausnummer),
	_postleitzahl(postleitzahl),
	_stadt(stadt)
{}

string Anschrift::text() const					//Rückgabe der Anschrift als string
{
	stringstream sstr;

	sstr << _postleitzahl << " " << _stadt << ", " << _strasse << " " << _hausnummer;

	return sstr.str();
}

