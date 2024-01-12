/**
 * OPR-Praktikum SS 2012
 * Aufgabe 10
 * @author Thomas Mahr
 */

#include "PrueffolgeSport.h"
#include "Sportler.h"
#include "Uebung.h"
#include "EnergieFormatJoule.h"
#include "EnergieFormatSchokolade.h"
#include <cmath>
#include <sstream>
using namespace std;

const Sportler PrueffolgeSport::SPORTLER("Hugo", 85, 0.6);
const Bankdruecken PrueffolgeSport::BANKDRUECKEN;


PrueffolgeSport::PrueffolgeSport()
{
	anmelden("Sportler", &pruefungSportler);
	anmelden("Wiederholung ausführen", &pruefungSportlerAusgabe);
	anmelden("Bankdrücken", &pruefungBankdruecken);
	anmelden("Bankdruecken ausgeben", &pruefungBankdrueckenAusgabe);
	anmelden("Wiederholungen ausführen", &pruefungWiederholungAusfuehren);
	anmelden("Übung Bankdrücken ausführen (Joule)", &pruefungUebungBankdrueckenJoule);
	anmelden("Übung Bankdrücken ausführen (Schokolade)", &pruefungUebungBankdrueckenSchokolade);
}

void PrueffolgeSport::pruefungSportler()
{
	Sportler sportler = SPORTLER;
	SICHERSTELLEN(sportler.name() == "Hugo");
	SICHERSTELLEN(sportler.koerpergewicht() == 85);
	SICHERSTELLEN(sportler.armlaenge() == 0.6);
	SICHERSTELLEN(sportler.energieUmsatz() == 0);
}

void PrueffolgeSport::pruefungSportlerAusgabe()
{
	stringstream s;
	s << "Sportler: " << SPORTLER << "!";
	SICHERSTELLEN(s.str() == "Sportler: Hugo: Koerpergewicht = 85 kg, Armlaenge = 0.6 m, Energieumsatz = 0 J!");
}

void PrueffolgeSport::pruefungBankdruecken()
{
	Bankdruecken geraet = BANKDRUECKEN;
	SICHERSTELLEN(geraet.eingestelltesGewicht() == 0);
	geraet.gewichtEinstellen(100);
	SICHERSTELLEN(geraet.eingestelltesGewicht() == 100);
	Sportler sportler = SPORTLER;
	SICHERSTELLEN(abs(geraet.energieProWiederholung(SPORTLER) - Bankdruecken::ERDBESCHLEUNIGUNG * 100 * SPORTLER.armlaenge()) < 0.1);
}

void PrueffolgeSport::pruefungBankdrueckenAusgabe()
{
	stringstream s;
	Bankdruecken geraet = BANKDRUECKEN;
	geraet.gewichtEinstellen(120);
	s << "Geraet: " << geraet << "!";
	SICHERSTELLEN(s.str() == "Geraet: Auf dem Geraet Bankdruecken sind 120 kg eingestellt.!");
}

void PrueffolgeSport::pruefungWiederholungAusfuehren()
{
	Sportler sportler = SPORTLER;

	Bankdruecken geraet1 = BANKDRUECKEN;
	geraet1.gewichtEinstellen(100);
	sportler.wiederholungAusfuehren(geraet1);
	SICHERSTELLEN(abs(sportler.energieUmsatz() - 100 * Bankdruecken::ERDBESCHLEUNIGUNG * sportler.armlaenge() / Sportler::WIRKUNGSGRAD) < 0.1);
	sportler.wiederholungAusfuehren(geraet1);
	SICHERSTELLEN(abs(sportler.energieUmsatz() - 2 * 100 * Bankdruecken::ERDBESCHLEUNIGUNG * sportler.armlaenge() / Sportler::WIRKUNGSGRAD) < 0.1);
}

void PrueffolgeSport::pruefungUebungBankdrueckenJoule()
{
	stringstream s;
	Sportler sportler = SPORTLER;
	Bankdruecken geraetBankdruecken;

	int anzahlSaetze = 3;
	int anzahlWiederholungenProSatz = 10;
	double gewicht = 100;
	Uebung<EnergieFormatJoule> uebung(sportler, geraetBankdruecken, anzahlSaetze, anzahlWiederholungenProSatz, gewicht);
	uebung.ausfuehren(s);
	SICHERSTELLEN(abs(sportler.energieUmsatz() - 3 * 10 * 100 * Bankdruecken::ERDBESCHLEUNIGUNG * sportler.armlaenge() / Sportler::WIRKUNGSGRAD) < 0.1);
	cout << "*** " << uebung.energieUmsatz() << endl;
	SICHERSTELLEN(uebung.energieUmsatz() == "70.63 kJ");
}

void PrueffolgeSport::pruefungUebungBankdrueckenSchokolade()
{
	stringstream s;
	Sportler sportler = SPORTLER;
	Bankdruecken geraetBankdruecken;

	int anzahlSaetze = 3;
	int anzahlWiederholungenProSatz = 10;
	double gewicht = 100;
	Uebung<EnergieFormatSchokolade> uebung(sportler, geraetBankdruecken, anzahlSaetze, anzahlWiederholungenProSatz, gewicht);
	uebung.ausfuehren(s);
	SICHERSTELLEN(abs(sportler.energieUmsatz() - 3 * 10 * 100 * Bankdruecken::ERDBESCHLEUNIGUNG * sportler.armlaenge() / Sportler::WIRKUNGSGRAD) < 0.1);
	cout << "*** " << uebung.energieUmsatz() << endl;
	SICHERSTELLEN(uebung.energieUmsatz() == "0.032 Tafeln Schokolade");
}