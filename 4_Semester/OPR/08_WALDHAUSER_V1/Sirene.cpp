/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#include "Sirene.h"

int Sirene::_nummer = 1;

Sirene::Sirene()
{
	_name = "Sirene Nr. " + std::to_string(_nummer);
	_nummer++;
}

void Sirene::alarmieren()
{
	std::cout << _name << " geht an (heul)" << std::endl;
	alarmiert = true;
}

std::string Sirene::liefereName() const
{
	return _name;
}
