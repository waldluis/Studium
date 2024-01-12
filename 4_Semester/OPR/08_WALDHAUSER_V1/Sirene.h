/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#pragma once
#include "AlarmierbarImpl.h"
#include <string>

class Sirene : public AlarmierbarImpl
{
private:
	std::string _name;
	static int _nummer;

public:
	Sirene();
	virtual void alarmieren();
	virtual std::string liefereName() const;
};

