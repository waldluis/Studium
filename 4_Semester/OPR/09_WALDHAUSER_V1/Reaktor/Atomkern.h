/**
* $Author: WaldhauserLu $
* $Rev: 118 $
* $Date: 2021-06-05 10:15:00 +0100 (SA, 6. Juni 2021) $
*/

#pragma once
#include <string>
#include <iostream>

class Atomkern
{
private:
	std::string _symbol;
	int _massenzahl;
	int _ordnungszahl;

public:
	const static Atomkern PROTON;
	const static Atomkern NEUTRON;

	Atomkern();
	Atomkern(int masse, int ordnung);
	Atomkern(std::string name, int masse, int ordnung);

	int ordnungszahl() const;
	int massenzahl() const;
	std::string symbol() const;
	Atomkern liefereAtomkern() const;

	friend std::ostream& operator<<(std::ostream& os, const Atomkern& atom);
	Atomkern operator+= (const Atomkern& atom);
	const Atomkern operator+ (const Atomkern& atom) const;
	Atomkern operator-= (const Atomkern& atom);
	const Atomkern operator- (const Atomkern& atom) const;
	bool operator== (const Atomkern& atom);
	friend bool operator==(const Atomkern& atom, const Atomkern& atom2);
	friend Atomkern operator* (int i, const Atomkern& atom);

protected:
	void symbolAendern();
};
