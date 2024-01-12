/**
 * @author Thomas Mahr (www.tmahr.de)
 * @version $Rev: 122 $
 * @date $Date: 2015-03-22 10:50:38 +0100 (So, 22. Mär 2015) $
 */
#pragma once
#include <string>
class Datensatz;

/**
 * Dient zur Darstellung eines Datensatzes in einem Diagramm.
 */
struct Abbildung
{
	/**
	 * Destruktor
	 */
	virtual ~Abbildung() {}

	/**
	 * Stellt einen Datensatz dar.
	 * @param datensatz Datensatz
	 * @param titel Titel des Diagramms
	 * @param xAchse Name der x-Achse
	 * @param yAchse Name der y-Achse
	 */
	virtual void anzeigen(const Datensatz& datensatz, const std::string& titel, const std::string& xAchse, const std::string& yAchse) = 0;
};

