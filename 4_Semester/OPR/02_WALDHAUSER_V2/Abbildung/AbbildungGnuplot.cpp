/**
 * @author Thomas Mahr (www.tmahr.de)
 * @version $Rev: 122 $
 * @date $Date: 2015-03-22 10:50:38 +0100 (So, 22. Mär 2015) $
 */
#include "AbbildungGnuplot.h"
#include "Datensatz.h"
#include <fstream>
#include <iostream>

void AbbildungGnuplot::anzeigen(const Datensatz& datensatz, const std::string& titel, const std::string& xAchse, const std::string& yAchse)
{
	std::ofstream os(titel + ".dat");
	for (int i = 0; i < datensatz.laenge(); i++)
	{
		os << datensatz.x(i) << " " << datensatz.y(i) << std::endl;
	}
	os.close();

	gnuplot(titel, xAchse, yAchse);
}

void AbbildungGnuplot::gnuplot(const std::string& titel, const std::string& xAchse, const std::string& yAchse)
{
	const std::string dateiname = titel + ".gp";
	std::ofstream os(dateiname);
	os << "set grid\n"
		<< "set title \"" << titel << "\"\n"
		<< "set xlabel\"" << xAchse << "\"\n"
		<< "set ylabel\"" << yAchse << "\"\n"
		<< "set nokey\n"
		<< "set terminal pdf\n"
		<< "set output '" << titel << ".pdf'\n"
		<< "plot " << "\"" << titel << ".dat\" with linespoints\n"
		//			<< "pause -1\n"
		;
	os.close();

	std::string kommando = "gnuplot " + dateiname;
	int ret = system(kommando.c_str());
	if (ret != 0)
	{
		std::cerr << "Fehler beim Ausführen von " << kommando.c_str();
	}
}
