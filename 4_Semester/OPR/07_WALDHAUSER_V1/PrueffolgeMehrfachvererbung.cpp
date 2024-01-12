/**
* $Author: MahrTh $
* $Rev: 588 $
* $Date: 2021-05-08 13:05:25 +0200 (Sa, 08. Mai 2021) $
* ACHTUNG: Diese Datei darf nicht verändert werden!
*/
#include "PrueffolgeMehrfachvererbung.h"
#include "A.h"
#include "B.h"
#include "C.h"
#include "D.h"
using namespace std;

PrueffolgeMehrfachvererbung::PrueffolgeMehrfachvererbung()
{
	anmelden("Prüfe A", &pruefungA);
	anmelden("Prüfe B", &pruefungB);
	anmelden("Prüfe C", &pruefungC);
	anmelden("Prüfe D", &pruefungD);
	anmelden("Prüfe Anzahl A-Objekte", &pruefungAnzahlObjekte);
	anmelden("Prüfe Objektgröße", &pruefungObjektgroesse);
	anmelden("Prüfe Vererbungsbeziehung", &pruefungVererbung);
}

void PrueffolgeMehrfachvererbung::pruefungA()
{
	A a1(1);
	SICHERSTELLEN(a1.g().compare("A::g-1") == 0);
	A a2(2);
	SICHERSTELLEN(a2.g().compare("A::g-2") == 0);
}

void PrueffolgeMehrfachvererbung::pruefungB()
{
	B b1(2);
	SICHERSTELLEN(b1.g().compare("A::g-4") == 0);
	SICHERSTELLEN(b1.h().compare("B::h-2 A::f-4") == 0);
	B b2(3);
	SICHERSTELLEN(b2.g().compare("A::g-9") == 0);
	SICHERSTELLEN(b2.h().compare("B::h-3 A::f-9") == 0);
}

void PrueffolgeMehrfachvererbung::pruefungC()
{
	C c1(3);
	SICHERSTELLEN(c1.g().compare("A::g-27") == 0);
	SICHERSTELLEN(c1.h().compare("C::h-3 A::f-27") == 0);
	C c2(4);
	SICHERSTELLEN(c2.g().compare("A::g-64") == 0);
	SICHERSTELLEN(c2.h().compare("C::h-4 A::f-64") == 0);
}

void PrueffolgeMehrfachvererbung::pruefungD()
{
	D d1(4);
	SICHERSTELLEN(d1.g().compare("D::g-4") == 0);
	SICHERSTELLEN(d1.h().compare("D::h-4 B::h-4 A::f-16 C::h-4 A::f-64") == 0);
	D d2(5);
	SICHERSTELLEN(d2.g().compare("D::g-5") == 0);
	SICHERSTELLEN(d2.h().compare("D::h-5 B::h-5 A::f-25 C::h-5 A::f-125") == 0);
}

void PrueffolgeMehrfachvererbung::pruefungAnzahlObjekte()
{
	{
		SICHERSTELLEN(A::anzahlObjekte() == 0);
		A a(11);
		B b(12);
		C c(13);
		D d(14);
		SICHERSTELLEN(A::anzahlObjekte() == 5);
	}
	SICHERSTELLEN(A::anzahlObjekte() == 0);
}

void PrueffolgeMehrfachvererbung::pruefungObjektgroesse()
{
	A a(21);
	B b(22);
	C c(23);
	D d(24);
	SICHERSTELLEN(sizeof(b) / sizeof(a) == 2);
	SICHERSTELLEN(sizeof(c) / sizeof(a) == 2);
	SICHERSTELLEN(sizeof(d) / sizeof(a) == 5);
}

void PrueffolgeMehrfachvererbung::pruefungVererbung()
{
	B b(3);
	C c(4);
	D d(5);
	A& ab = b;
	A& ac = c;
	B& bd = d;
	SICHERSTELLEN(ab.g().compare("A::g-9") == 0);
	SICHERSTELLEN(ac.g().compare("A::g-64") == 0);
	SICHERSTELLEN(bd.g().compare("A::g-25") == 0);
}

