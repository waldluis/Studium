/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#include "BewegungsDetektor.h"

BewegungsDetektor::BewegungsDetektor(std::string name):
	_name(name), DetektorImpl(name)
{
	std::cout << "Detektor " << name << " aufbauen" << std::endl;
}

void BewegungsDetektor::ausloesen()
{
	std::cout << "BewegungsDetektor " << _name << " detektiert Bewegung" << std::endl;

	for (auto i : empfaenger)
	{
		i->alarmieren();
	}
}
