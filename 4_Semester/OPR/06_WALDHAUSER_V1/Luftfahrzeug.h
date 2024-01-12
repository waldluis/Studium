/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-07-7 9:15:00 +0100 (Fr, 07. Mai 2021) $
*/
#pragma once
#include <string>
#include "Verkehrsmittel.h"

class Luftfahrzeug : public Verkehrsmittel
{
private:
	int maxFlughoehe_;

public:
	Luftfahrzeug(const std::string& name, int hoehe);
	Luftfahrzeug(const Luftfahrzeug& l);
	int maxFlughoehe() const;
	std::string text() const;
};
