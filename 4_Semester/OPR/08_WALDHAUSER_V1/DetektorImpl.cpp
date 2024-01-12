/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#include "DetektorImpl.h"

DetektorImpl::DetektorImpl(std::string name):
	_name(name)
{}

DetektorImpl::~DetektorImpl()
{
	std::cout << "Detektor " << _name << " abbauen" << std::endl;
	int hilf = empfaenger.size();
	for (int i = 0; i < hilf; i++)
	{
		std::cout << empfaenger[0]->liefereName() << " abmelden" << std::endl;
		empfaenger.erase(empfaenger.begin());
	}
}

void DetektorImpl::anschliessen(Alarmierbar& alamierbar)
{
	std::cout << alamierbar.liefereName() << " an " << _name << " anschliessen" << std::endl;
	empfaenger.push_back(&alamierbar);
}

void DetektorImpl::alamieren()
{
	for (auto i : empfaenger)
	{
		i->alarmieren();
	}
}
