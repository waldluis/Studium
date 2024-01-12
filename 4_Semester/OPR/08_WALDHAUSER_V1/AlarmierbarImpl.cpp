/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#include "AlarmierbarImpl.h"

AlarmierbarImpl::AlarmierbarImpl() :
	alarmiert(false)
{}

void AlarmierbarImpl::alarmieren()
{
	alarmiert = true;
}

bool AlarmierbarImpl::istAlarmiert() const
{
	return alarmiert;
}

void AlarmierbarImpl::alarmZuruecksetzen()
{
	alarmiert = false;
}
