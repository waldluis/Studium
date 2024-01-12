/**
* $Author: MahrTh $
* $Rev: 122 $
* $Date: 2015-03-22 10:50:38 +0100 (So, 22. Mär 2015) $
* OPR-Praktikum: Aufgabe 1_Grundlagen/02_Kapselung/Flugkurve02: Variante 2
*/
#include "AbbildungGnuplot.h"
#include "Datensatz.h"
using namespace std;

int main()
{
	Datensatz datensatz;
	
	datensatz.hinzufuegen(0, 0);										//Daten aus Flugkurve übertragen
	datensatz.hinzufuegen(0.95, 0.85);
	datensatz.hinzufuegen(1.9, 1.6);
	datensatz.hinzufuegen(2.7, 2.1);
	datensatz.hinzufuegen(3.5, 2.6);
	datensatz.hinzufuegen(4.3, 2.9);
	datensatz.hinzufuegen(5, 3.1);
	datensatz.hinzufuegen(5.7, 3.2);
	datensatz.hinzufuegen(6.4, 3.2);
	datensatz.hinzufuegen(7, 3.2);
	datensatz.hinzufuegen(7.6, 3);
	datensatz.hinzufuegen(8.2, 2.7);
	datensatz.hinzufuegen(8.7, 2.3);
	datensatz.hinzufuegen(9.2, 1.9);
	datensatz.hinzufuegen(9.7, 1.4);
	datensatz.hinzufuegen(10, 0.77);
	datensatz.hinzufuegen(11, 0.12);
	


	datensatz.anzeigen("Flugkurve", "x", "y");
}