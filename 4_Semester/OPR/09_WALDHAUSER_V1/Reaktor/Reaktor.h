/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-05 10:15:00 +0100 (SA, 6. Juni 2021) $
*/

#pragma once
#include "Atomkern.h"

class Reaktor
{
private:
	Atomkern _inhalt;

public:
	Reaktor operator<(const Atomkern& atom);
	Reaktor operator>(const Atomkern& atom);
	const Atomkern operator*();
	Reaktor operator~();

protected:

};
