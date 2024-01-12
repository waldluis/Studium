/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-05-14 9:30:00 +0100 (Fr, 14. Mai 2021) $
*/

#pragma once
#include <iostream>
#include <string>
#include <sstream>

class A
{
private:
	int wert;

protected:
	std::string f()
	{
		std::stringstream hilf;
		hilf << "A::f-" << wert;
		return hilf.str();
	};

public:
	static int anzahlObjekte_;

	A(int i) : wert(i) { anzahlObjekte_++; };

	A(const A& a) : wert(a.wert) { anzahlObjekte_++; };

	~A() { anzahlObjekte_--; };

	std::string g()
	{
		std::stringstream hilf;
		hilf << "A::g-" << wert;
		return hilf.str();
	};

	static int anzahlObjekte()
	{
		return anzahlObjekte_;
	}
};

int A::anzahlObjekte_ = 0;
