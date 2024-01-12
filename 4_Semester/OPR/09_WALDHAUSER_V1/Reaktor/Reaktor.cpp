/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-05 10:15:00 +0100 (SA, 6. Juni 2021) $
*/

#include "Reaktor.h"

Reaktor Reaktor::operator<(const Atomkern& atom)
{
	_inhalt += atom;
	return *this;
}

Reaktor Reaktor::operator>(const Atomkern& atom)
{
	_inhalt -= atom;
	return *this;
}

const Atomkern Reaktor::operator*()
{
	return _inhalt;
}

Reaktor Reaktor::operator~()
{
	_inhalt -= _inhalt;
	return Reaktor();
}

