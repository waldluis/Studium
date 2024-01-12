/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-23 16:40:00 +0100 (Mo, 23. Apr 2021) $
*/

#include <vector>
#include <string>
#include <sstream>
#include "Zahl.h"
#include "Vektor.h"

using namespace std;

int Zahl::objektZaehler = 0;
Zahl Zahl::Null = 0;
Zahl Zahl::Eins = 1;

Zahl::Zahl(int z) :
	i(z)
{
	objektZaehler++;
}

Zahl::Zahl(const Zahl& z) :
	i(z.i)
{
	objektZaehler++;
}

Zahl::Zahl(const Vektor& v) :
	i(v.summe())
{
	objektZaehler++;
}

Zahl::~Zahl()
{
	objektZaehler--;
}

string Zahl::text() const
{
	stringstream hilf;
	hilf << i;

	return hilf.str();
}

int Zahl::wert() const
{
	return i;
}

Zahl Zahl::add(const Zahl& z) const
{
	Zahl hilf = z;
	hilf.i += i;

	return hilf;
}

Zahl& Zahl::add(const Zahl& z)
{
	i = i + z.i;
	return *this;
}

Zahl Zahl::sub(const Zahl& z) const
{
	Zahl hilf = z;
	hilf.i = i - z.i;

	return hilf;
}

Zahl& Zahl:: sub(const Zahl& z)
{
	i = i - z.i;
	return *this;
}

Zahl Zahl::mul(const Zahl& z) const
{
	Zahl hilf = z;
	hilf.i *= i;

	return hilf;
}

Zahl& Zahl::mul(const Zahl& z)
{
	i = i * z.i;
	return *this;
}

Zahl Zahl::div(const Zahl& z) const
{
	Zahl hilf = z;
	hilf.i = i / z.i;

	return hilf;
}

Zahl& Zahl::div(const Zahl& z)
{
	i = i / z.i;
	return *this;
}

int Zahl::anzahlObjekte()
{
	return objektZaehler;
}