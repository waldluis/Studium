/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#pragma once
#include <iostream>

class Alarmierbar;

class Detektor
{
public:
	virtual void anschliessen(Alarmierbar& alarm) = 0;
	virtual void ausloesen() = 0;
	virtual ~Detektor(){};
};

