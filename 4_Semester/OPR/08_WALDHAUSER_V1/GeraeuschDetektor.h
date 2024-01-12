/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-27 9:30:00 +0100 (Do, 27. Mai 2021) $
*/

#pragma once
#include "DetektorImpl.h"

class GeraeuschDetektor : public DetektorImpl
{
private:
	std::string _name;

public:
	GeraeuschDetektor(std::string name);
	virtual void ausloesen();
};