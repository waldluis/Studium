/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-07-7 9:15:00 +0100 (Fr, 07. Mai 2021) $
*/

#pragma once
#include <string>
#include "Verkehrsmittel.h"

class Radfahrzeug : public Verkehrsmittel
{
private:
	int anzahlRaeder_;

public:
	Radfahrzeug(const std::string& name, int i);
	Radfahrzeug(const Radfahrzeug& r);
	int anzahlRaeder() const;
	std::string text() const;
};