/**
 * @author Thomas Mahr (www.tmahr.de)
 * @version $Rev: 127 $
 * @date $Date: 2015-03-29 17:56:44 +0200 (So, 29. Mär 2015) $
 */
#pragma once
#include "Abbildung.h"
#include <string>

 /**
  * Stellt einen Datensatzes mittels Gnuplot dar: http://gnuplot.info/
  */
class AbbildungGnuplot : public Abbildung
{
private:

	/**
	 * Ruft Gnuplot auf.
	 * @param titel Titel des Diagramms
	 * @param xAchse Name der x-Achse
	 * @param yAchse Name der y-Achse
	 */
	static void gnuplot(const std::string& titel, const std::string& xAchse, const std::string& yAchse);

public:

	/**
	 * Stellt einen Datensatz mittels Gnuplot dar.
	 * @param datensatz Datensatz
	 * @param titel Titel des Diagramms
	 * @param xAchse Name der x-Achse
	 * @param yAchse Name der y-Achse
	 */
	void anzeigen(const Datensatz& datensatz, const std::string& titel, const std::string& xAchse, const std::string& yAchse);
};
