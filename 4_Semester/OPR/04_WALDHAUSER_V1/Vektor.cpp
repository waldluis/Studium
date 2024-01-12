/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-23 16:40:00 +0100 (Mo, 23. Apr 2021) $
*/

#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include "Vektor.h"
#include "Zahl.h"
#include <initializer_list>

using namespace std;

Vektor::Vektor(std::initializer_list<Zahl> z):
	werte(z)
{}

string Vektor::text() const
{
	stringstream hilf;
	hilf << "( ";

	for (unsigned int i = 0; i < werte.size(); i++)
	{
		hilf << werte[i].wert() << " ";
	}
	hilf << ")";

	return hilf.str();
}

int Vektor::laenge() const
{
	int hilf = 0;

	for (unsigned int i = 0; i < werte.size(); i++)
	{
		hilf += werte[i].wert() * werte[i].wert();    //Addieren der Quadrate der jeweiligen Richtung des Vektors
	}
	hilf = sqrt(hilf);

	return hilf;
}

int Vektor::summe() const
{
	int zahl = 0;

	for (unsigned int i = 0; i < werte.size(); i++)
	{
		zahl = zahl + werte[i].wert();
	}
	return zahl;
}

Vektor& Vektor::anhaengen(const Vektor& v)
{
	for (unsigned int i = 0; i < v.werte.size(); i++)
	{
		werte.push_back(v.werte[i].wert());
	}
	return *this;
}

Vektor& Vektor::add(const Vektor& v)
{
	for (unsigned i = 0; i < werte.size(); i++)
	{
		werte[i].add(v.werte[i]);
	}
	return *this;
}

Vektor& Vektor::mul(int z)
{
	for (unsigned int i = 0; i < werte.size(); i++)
	{
		werte[i].mul(z);
	}
	return *this;
}

Vektor& Vektor::sub(const Vektor& v)
{
	for (unsigned int i = 0; i < werte.size(); i++)
	{
		werte[i].sub(v.werte[i]);
	}
	return *this;
}

Vektor& Vektor::div(int z)
{
	for (unsigned int i = 0; i < werte.size(); i++)
	{
		werte[i].div(z);
	}
	return *this;
}
