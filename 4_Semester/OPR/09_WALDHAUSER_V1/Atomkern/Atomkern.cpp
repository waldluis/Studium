/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-05 10:15:00 +0100 (SA, 6. Juni 2021) $
*/

#include "Atomkern.h"

class ostream;

const Atomkern Atomkern::PROTON = { "", 1, 1 };
const Atomkern Atomkern::NEUTRON = { "", 1, 0 };

Atomkern::Atomkern(std::string symbol, int masse, int ordnung):
	_symbol(symbol),
	_massenzahl(masse),
	_ordnungszahl(ordnung)
{}

int Atomkern::ordnungszahl() const
{
	return _ordnungszahl;
}

int Atomkern::massenzahl() const
{
	return _massenzahl;
}

std::string Atomkern::symbol() const
{
	return _symbol;
}

Atomkern Atomkern::operator+=(const Atomkern& atom)
{
	_massenzahl += atom.massenzahl();
	_ordnungszahl += atom.ordnungszahl();

	return *this;
}

const Atomkern Atomkern::operator+(const Atomkern& atom) const
{
	Atomkern hilf = *this;

	hilf += atom;
	hilf.symbolAendern();

	return hilf;
}

bool Atomkern::operator==(const Atomkern& atom)
{
	if (atom.symbol() == _symbol && atom.massenzahl() == _massenzahl && atom.ordnungszahl() == _ordnungszahl)
	{
		return true;
	}
	else return false;
}

bool operator==(const Atomkern& atom, const Atomkern& atom2)
{
	if (atom.symbol() == atom2.symbol() && atom.massenzahl() == atom2.massenzahl() && atom.ordnungszahl() == atom2.ordnungszahl())
	{
		return true;
	}
	else return false;
}

Atomkern Atomkern::operator-=(const Atomkern& atom)
{
	_massenzahl -= atom.massenzahl();
	_ordnungszahl -= atom.ordnungszahl();

	return *this;
}

const Atomkern Atomkern::operator-(const Atomkern& atom) const
{
	Atomkern hilf = *this;

	hilf -= atom;
	hilf.symbolAendern();

	return hilf;
}

std::ostream& operator<<(std::ostream& os, const Atomkern& atom)
{
	os << atom.symbol() << "(" << atom.massenzahl() << "," << atom.ordnungszahl() << ")";
	return os;
}

Atomkern operator*(int i, const Atomkern& atom)
{
	Atomkern hilf = atom;

	hilf._massenzahl *= i;
	hilf._ordnungszahl *= i;

	return hilf;
}

void Atomkern::symbolAendern()
{
	if(ordnungszahl() == 1)
	{
		_symbol = "H";
	}
	else if (ordnungszahl() == 2)
	{
		_symbol = "He";
	}
	else if (ordnungszahl() == 94)
	{
		_symbol = "Pu";
	}
}