/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-14 9:30:00 +0100 (Fr, 14. Mai 2021) $
*/

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "A.h"

class B : public A
{
private:
	int wert;

public:
	B(int i) : A(i *i), wert(i) {};

	B(const B& b) : A(b), wert(b.wert) {};

	std::string h()
	{
		std::stringstream hilf;
		hilf << "B::h-" << wert << " " << A::f();

		return hilf.str();
	};
};
