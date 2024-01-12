/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-16 14:00:00 +0100 (Fr, 16. Apr 2021) $
*/

#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Anschrift.h"

using namespace std;

class Person 
{
private:
	string _name;
	Anschrift _anschrift;
	std::vector<Person*> _freunde;
	bool istFreund(const Person& freund) const;

public:
	Person(); 
	Person(const string& name); 
	string name() const; 
	void setzeAnschrift(Anschrift adresse); 
	void setzeAnschrift(const string& straﬂe, const string& hausnummer, int postleitzahl, const string& stadt); //fertig
	Anschrift anschrift() const; 
	void befreunden(Person& freund);
	string text() const;
	
};