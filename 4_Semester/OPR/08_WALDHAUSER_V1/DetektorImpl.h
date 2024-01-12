/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#pragma once
#include <string>
#include <vector>
#include "Alarmierbar.h"
#include "Detektor.h"

class DetektorImpl: public Detektor
{
private:
	std::string _name;

public:
	DetektorImpl(std::string name);
	virtual ~DetektorImpl();
	virtual void anschliessen(Alarmierbar& alamierbar);

protected:
	virtual void alamieren();
	std::vector<Alarmierbar*> empfaenger;
};
