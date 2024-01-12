/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#include "Flutlicht.h"

int Flutlicht::_nummer = 1;

Flutlicht::Flutlicht(int staerke):
	_lumen(staerke)
{
	_name = "Flutlicht Nr. " + std::to_string(_nummer);
	_nummer++;
}

void Flutlicht::alarmieren()
{
	std::cout << _name << " erstrahlt mit " << _lumen << " Lumen" << std::endl;
	alarmiert = true;
}

std::string Flutlicht::liefereName() const
{ 
	return _name;
}
