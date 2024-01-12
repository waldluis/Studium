/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#pragma once
#include "AlarmierbarImpl.h"
#include <string>

class Flutlicht : public AlarmierbarImpl
{
private:
	int _lumen;
	std::string _name;
	static int _nummer;

public:
	Flutlicht(int staerke);
	virtual void alarmieren();
	virtual std::string liefereName() const;
};