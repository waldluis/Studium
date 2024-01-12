/**
 * OPR-Praktikum SS 2012
 * Aufgabe 10
 * @author Thomas Mahr
 */

#include "PrueffolgeSport.h"
#include "Sportler.h"
#include "Bankdruecken.h"
#include "Uebung.h"
#include "EnergieFormatSchokolade.h"
using namespace std;

void prueffolge()
{
	PrueffolgeSport prueffolge;
	prueffolge.ausfuehren();
}

void beispiel1()
{
	Sportler hugo("Hugo", 85, 0.8);
	cout << "\nAnwendungsbeispiel 1: " << hugo << endl;
	Bankdruecken geraetBankdruecken;
	int anzahlSaetze = 3;
	int anzahlWiederholungenProSatz = 10;
	double gewicht = 100;
	Uebung<EnergieFormatSchokolade> bankdruecken(hugo, geraetBankdruecken, anzahlSaetze, anzahlWiederholungenProSatz, gewicht);
	bankdruecken.ausfuehren(cout);
}

void beispiel2()
{
	Sportler clark("Clark Kent", 85, 0.8);
	cout << "\nAnwendungsbeispiel 2: " << clark << endl;
	Bankdruecken geraetBankdruecken;

	int anzahlSaetze = 3;

	// Diese beiden Parameter sind so einzustellen, dass Clark Kent 1 Tafel Schokolade "verbrennt":
	const int anzahlWiederholungenProSatz = 234;
	const double gewicht = 100;

	Uebung<EnergieFormatSchokolade> extremBankdruecken(clark, geraetBankdruecken, anzahlSaetze, anzahlWiederholungenProSatz, gewicht);
	extremBankdruecken.ausfuehren(cout);
}

int main()
{
	prueffolge();
	beispiel1();
	beispiel2();
}