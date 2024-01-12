/**
 * @author Thomas Mahr (www.tmahr.de)
 * @version $Rev: 122 $
 * @date $Date: 2015-03-22 10:50:38 +0100 (So, 22. Mär 2015) $
 */
#pragma once
#include <string>
#include <vector>

 /**
  * Repräsentiert einen Datensatz aus x-y-Paaren.
  */
class Datensatz
{
private:

	std::vector<double> _x;
	std::vector<double> _y;

public:

	/**
	 * Fügt dem Datensatz ein x-y-Paar hinzu.
	 * @param x x
	 * @param y y
	 */
	void hinzufuegen(double x, double y)
	{
		_x.push_back(x);
		_y.push_back(y);
	}

	/**
	 * Liefert die Anzahl der x-y-Paare zurück.
	 * @return Anzahl der x-y-Paare
	 */
	int laenge() const
	{
		return _x.size();
	}

	/**
	 * Liefert den x-Wert an einer bestimmten Position innerhalb des Datensatzes zurück.
	 * @param index Position innerhalb des Datensatzes
	 * @return x-Wert
	 */
	double x(int index) const
	{
		return _x[index];
	}

	/**
	 * Liefert den y-Wert an einer bestimmten Position innerhalb des Datensatzes zurück.
	 * @param index Position innerhalb des Datensatzes
	 * @return y-Wert
	 */
	double y(int index) const
	{
		return _y[index];
	}

	/**
	 * Stellt den Datensatz dar.
	 * @param titel Titel des Diagramms
	 * @param xAchse Name der x-Achse
	 * @param yAchse Name der y-Achse
	 */
	void anzeigen(std::string titel, std::string xAchse, std::string yAchse);
};

