/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#pragma once
#include "Alarmierbar.h"

class AlarmierbarImpl: public Alarmierbar
{
protected:
	bool alarmiert;

public:
	AlarmierbarImpl();
	virtual void alarmieren();
	virtual bool istAlarmiert() const;
	virtual void alarmZuruecksetzen();
};
