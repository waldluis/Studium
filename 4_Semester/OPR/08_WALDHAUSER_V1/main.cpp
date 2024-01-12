#include "Flutlicht.h"
#include "Sirene.h"
#include "BewegungsDetektor.h"
#include "GeraeuschDetektor.h"

using namespace std;

void alarmFuerAlleAnzeigen(vector<Alarmierbar*>* alarme);
void alarmFuerAlleZuruecksetzen(vector<Alarmierbar*>* alarme);

int main() {

	cout << "*** Alarmsystem aufbauen\n";

	vector<Alarmierbar*> vectorAlarmierbar;
	Detektor* detektor[2];

	detektor[0] = new BewegungsDetektor("BD1");

	Sirene sirene;
	vectorAlarmierbar.push_back(&sirene);
	detektor[0]->anschliessen(sirene);

	int lumen = 5000;
	const int N_FLUTLICHT = 3;
	Flutlicht* flutlicht[N_FLUTLICHT];
	for (int i = 0; i < N_FLUTLICHT; i++) {
		flutlicht[i] = new Flutlicht(lumen * (i + 1));
		vectorAlarmierbar.push_back(flutlicht[i]);
		detektor[0]->anschliessen(*flutlicht[i]);
	}
	detektor[1] = new GeraeuschDetektor("GD1");
	detektor[1]->anschliessen(sirene);
	detektor[1]->anschliessen(*flutlicht[1]);

	cout << "*** Alarmsystem testen\n";
	detektor[0]->ausloesen();
	alarmFuerAlleAnzeigen(&vectorAlarmierbar);
	alarmFuerAlleZuruecksetzen(&vectorAlarmierbar);
	alarmFuerAlleAnzeigen(&vectorAlarmierbar);
	detektor[1]->ausloesen();
	alarmFuerAlleAnzeigen(&vectorAlarmierbar);

	cout << "*** Alarmsystem abbauen\n";
	delete detektor[0];
	delete detektor[1];
	for (auto f : flutlicht) {
		delete f;
	}
}

void alarmFuerAlleAnzeigen(vector<Alarmierbar*>* alarme)
{
	for (auto i : *alarme)
	{
		if (i->istAlarmiert() == true)
		{
			std::cout << i->liefereName() << ": Alarm ist an" << std::endl;
		}
		else
		{
			std::cout << i->liefereName() << ": Alarm ist aus" << std::endl;
		}

	}
}

void alarmFuerAlleZuruecksetzen(vector<Alarmierbar*>* alarme)
{
	for (auto i : *alarme)
	{
		i->alarmZuruecksetzen();
	}
}