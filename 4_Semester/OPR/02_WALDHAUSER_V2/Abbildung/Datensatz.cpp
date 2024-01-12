/**
 * @author Thomas Mahr (www.tmahr.de)
 * @version $Rev: 122 $
 * @date $Date: 2015-03-22 10:50:38 +0100 (So, 22. Mär 2015) $
 */
#include "Datensatz.h"
#include "AbbildungGnuplot.h"

void Datensatz::anzeigen(std::string titel, std::string xAchse, std::string yAchse)
{
	AbbildungGnuplot abbildung;
	abbildung.anzeigen(*this, titel, xAchse, yAchse);
}
