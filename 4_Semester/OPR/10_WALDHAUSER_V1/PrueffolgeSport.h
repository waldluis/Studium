/**
 * OPR-Praktikum SS 2012
 * Aufgabe 10
 * @author Thomas Mahr
 */

#pragma once
#include "Prueffolge.h"
#include "Sportler.h"
#include "Bankdruecken.h"

class PrueffolgeSport : public Prueffolge
{
public:

	PrueffolgeSport();

private:

	static void pruefungSportler();
	static void pruefungSportlerAusgabe();
	static void pruefungBankdruecken();
	static void pruefungBankdrueckenAusgabe();
	static void pruefungWiederholungAusfuehren();
	static void pruefungUebungBankdrueckenJoule();
	static void pruefungUebungBankdrueckenSchokolade();

	static const Sportler SPORTLER;
	static const Bankdruecken BANKDRUECKEN;
};
