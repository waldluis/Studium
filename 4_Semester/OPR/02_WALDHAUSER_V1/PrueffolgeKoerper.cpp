/**
* $Author: MahrTh $
* $Rev: 402 $
* $Date: 2017-10-02 11:22:56 +0200 (Mo, 02. Okt 2017) $
*
* ACHTUNG: Diese Datei darf nicht verändert werden!
*/
#include "PrueffolgeKoerper.h"
#include "Koerper.h"
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

PrueffolgeKoerper::PrueffolgeKoerper()
{
	anmelden("Prüfe Kinematik", &pruefungKinematik);
}

void PrueffolgeKoerper::pruefungKinematik()
{
	vector<Vektor> referenzPosition;

	referenzPosition.push_back(Vektor(0.95, 0.8519));
	referenzPosition.push_back(Vektor(1.8525, 1.56311));
	referenzPosition.push_back(Vektor(2.70987, 2.14065));
	referenzPosition.push_back(Vektor(3.52438, 2.59122));
	referenzPosition.push_back(Vektor(4.29816, 2.92116));
	referenzPosition.push_back(Vektor(5.03325, 3.1365));
	referenzPosition.push_back(Vektor(5.73159, 3.24297));
	referenzPosition.push_back(Vektor(6.39501, 3.24602));
	referenzPosition.push_back(Vektor(7.02526, 3.15082));
	referenzPosition.push_back(Vektor(7.624, 2.96228));
	referenzPosition.push_back(Vektor(8.1928, 2.68507));
	referenzPosition.push_back(Vektor(8.73316, 2.32361));
	referenzPosition.push_back(Vektor(9.2465, 1.88213));
	referenzPosition.push_back(Vektor(9.73417, 1.36463));
	referenzPosition.push_back(Vektor(10.1975, 0.774896));
	referenzPosition.push_back(Vektor(10.6376, 0.116551));

	// Körper:
	const float MASSE = 10;
	const Vektor START_POSITION = { 0,0 };
	const Vektor START_GESCHWINDIGKEIT = { 10,10 };
	Koerper koerper(MASSE, START_POSITION, START_GESCHWINDIGKEIT);

	// Parametrierung der auf den Körper wirkende Kräfte:
	const Vektor BESCHLEUNIGUNG_GRAVITATION = { 0, -9.81 }; // [m/s^2]
	const float REIBUNGSKOEFFIZIENT = -5; // [kg/s]

	// Simulation:
	cout << endl;
	const float dt = 0.1;
	for (unsigned int i = 0; i < referenzPosition.size(); i++)
	{
		// Bestimmung der neuen Beschleunigung
		Vektor beschleunigung;
		beschleunigung = koerper.liefereGeschwindigkeit();
		beschleunigung.mul(REIBUNGSKOEFFIZIENT / koerper.liefereMasse());
		beschleunigung.add(BESCHLEUNIGUNG_GRAVITATION);

		// Ermittlung der neuen Position und neuen Geschwindigkeit
		koerper.bewegen(beschleunigung, dt);

		// Ermittle Differenz zwischen Position des Körpers und Referenzposition:
		Vektor differenzVektor = referenzPosition[i].diff(koerper.lieferePosition());

		// Prüfung erfolgreich falls relative Abweichung < 1 %
		SICHERSTELLEN(differenzVektor.betrag() < 0.01 * referenzPosition[i].betrag());
	}
}
