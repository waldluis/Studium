/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-04-23 16:40:00 +0100 (Mo, 23. Apr 2021) $
*/

#pragma once

#include <vector>
#include <string>
#include <sstream>

class Vektor;				//forward declaration

class Zahl {
private:
	int i;
	static int objektZaehler;
	
public:
	static Zahl Null;
	static Zahl Eins;

	Zahl(int z);						
	Zahl(const Zahl& z);				
	Zahl(const Vektor& v);
	~Zahl();							
	static int anzahlObjekte();			
	int wert() const;					
	std::string text() const;			
	Zahl add(const Zahl& z) const;		
	Zahl& add(const Zahl& z);			
	Zahl sub(const Zahl& z) const;		
	Zahl& sub(const Zahl& z);			
	Zahl mul(const Zahl& z) const;		
	Zahl& mul(const Zahl& z);			
	Zahl div(const Zahl& z) const;		
	Zahl& div(const Zahl& z);			
};