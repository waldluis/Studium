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
#include "C.h"

class D : public B, public C
{
private:
	int wert;

public:
	D(int i) : B(i), C(i), wert(i) {};

	std::string h()
	{
		std::stringstream hilf;
		hilf << "D::h-" << wert << " " << B::h() << " " << C::h();
		return hilf.str();
	};

	std::string g()
	{
		std::stringstream hilf;
		hilf << "D::g-" << wert;
		return hilf.str();
	}
};
