/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-16 14:00:00 +0100 (Fr, 16. Apr 2021) $
*/

#pragma once
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

class Anschrift {
private:
	string _strasse;
	string _hausnummer;
	int _postleitzahl;
	string _stadt;

public:
	Anschrift();
	Anschrift(const string& strasse, const string& hausnummer, int postleitzahl, const string& stadt);
	string text() const;
};
