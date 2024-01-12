/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-07-7 9:15:00 +0100 (Fr, 07. Mai 2021) $
*/
#pragma once
#include <string>
#include "Vektor.h"

class Verkehrsmittel
{
private:
	std::string name_;
	Vektor position_;
	
public:
	Verkehrsmittel(const std::string& n);
	Verkehrsmittel(const Verkehrsmittel& v);
	~Verkehrsmittel();
	std::string text() const;
	void bewegeZu(const Vektor& v);
	const std::string& name() const;
	const Vektor& position() const;
};
