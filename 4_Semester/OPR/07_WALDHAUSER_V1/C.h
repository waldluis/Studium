/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-14 9:30:00 +0100 (Fr, 14. Mai 2021) $
*/

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "B.h"

class C : public A
{
private:
	int wert;

public:
	C(int i) : A(i *i *i), wert(i) {};

	C(const C& c) : A(c), wert(c.wert) {};

	std::string h()
	{
		std::stringstream hilf;
		hilf << "C::h-" << wert << " " << A::f();

		return hilf.str();
	};
};
