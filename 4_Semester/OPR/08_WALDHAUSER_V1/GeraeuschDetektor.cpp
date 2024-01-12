/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#include "GeraeuschDetektor.h"

GeraeuschDetektor::GeraeuschDetektor(std::string name):
	_name(name), DetektorImpl(name)
{
	std::cout << "Detektor " << name << " aufbauen" << std::endl;
}

void GeraeuschDetektor::ausloesen()
{
	std::cout << "GeraeuschDetektor " << _name << " detektiert Geraeusch" << std::endl;

	for (auto i : empfaenger)
	{
		i->alarmieren();
	}
}
