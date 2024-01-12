/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#pragma once
#include <iostream>
#include <string>

class Alarmierbar
{
public:
	virtual void alarmieren() = 0;
	virtual std::string liefereName() const = 0;
	virtual bool istAlarmiert() const = 0;
	virtual void alarmZuruecksetzen() = 0;
	virtual ~Alarmierbar() {};
};
