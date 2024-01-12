/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-16 14:00:00 +0100 (Fr, 16. Apr 2021) $
*/

#include "Person.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Person::Person() :						//Defaultkonstruktor 
	_name("Anonymos"),
	_anschrift(),						//Aufruf des Defaultkonstruktors von Adresse
	_freunde()
{
	_freunde.push_back(NULL);			//Setzen eines Nullpointers, da nicht gesetzte Pointer zu Fehlern führen
}

Person::Person(const string& name) :	//Konstruktor mit Namen, Rest unbekannt
	_name(name),
	_anschrift(),						//Aufruf des Defaultkonstruktors von Adresse
	_freunde()
{
	_freunde.push_back(NULL);			//Setzen eines Nullpointers, da nicht gesetzte Pointer zu Fehlern führen
};

string Person::name() const				//Rückgabe des Namens als string
{
	stringstream sstr;

	sstr << _name;

	return sstr.str();
}

Anschrift Person::anschrift() const
{
	return _anschrift;
}

void Person::setzeAnschrift(Anschrift adresse)		//Umkopieren der angegeben Anschrift auf Person
{
	_anschrift = adresse;
}

void Person::setzeAnschrift(const string& straße, const string& hausnummer, int postleitzahl, const string& stadt)  //Setzen der angegeben Anschrift mit Konstruktor der Anschrift Klasse
{
	Anschrift hilf(straße, hausnummer, postleitzahl, stadt);

	_anschrift = hilf;
}

bool Person::istFreund (const Person& freund) const
{
	int i = 0;

	while (_freunde[i] != NULL)						//Durchlaufen des Vektors, letzter Vektor Nullpointer
	{
		if (_freunde[i] == &freund)					//Vergleich ob Speicheradresse von Übergabe mit einem Freund übereinstimmt
			return true;

		i++;
	}
	return false;
}

void Person::befreunden(Person& freund)
{
	bool istfreund = istFreund(freund);

	if (istfreund == false)
	{
		int n = _freunde.size();				//Ermitteln der größe beider Vektoren
		int m = freund._freunde.size();
		_freunde[n-1] = &freund;				//Letztes Element mit Speicheradresse von Übergabe ersetzen
		freund._freunde[m-1] = this;			//Letztes Element mit Speicheradresse von aktueller Person ersetzen
		_freunde.push_back(NULL);				//Nullpointer ans Ende anhängen
		freund._freunde.push_back(NULL);		//Nullpointer ans Ende anhängen
	}
}

string Person::text() const						//Ausgabe des Inhalts einer Person als Text
{
	stringstream sstr;

	sstr << name() << "\n--- wohnhaft in " << _anschrift.text();

	if (_freunde[0] == NULL)
	{
		sstr << "\n--- keine Freunde";
	}
	else										//Ausgabe der Freunde
	{
		int i = 0;
		while (_freunde[i] != NULL)
		{
			sstr << "\n--- Freund: " << _freunde[i]->name() << "  (0x" << _freunde[i] << ")";
			i++;
		}
	}
	return sstr.str();
}