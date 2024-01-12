/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-23 16:40:00 +0100 (Mo, 23. Apr 2021) $
*/

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "Zahl.h"

class Vektor {
private:
	std::vector<Zahl> werte;

public:
	Vektor(std::initializer_list<Zahl> z);	
	std::string text() const;				
	int laenge() const;						
	Vektor& anhaengen(const Vektor& v);		
	Vektor& add(const Vektor& v);		
	Vektor& sub(const Vektor& v);		
	Vektor& mul(int z);					
	Vektor& div(int z);						
	int summe() const;						
};
