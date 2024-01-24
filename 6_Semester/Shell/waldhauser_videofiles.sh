#!/bin/bash

#Bearbeitung Aufgabe B.6 Luis Waldhauser								# Etwas knapp für einen header 

																		# Fehlermeldung / Hilfetext bei Aufruf ohne Parameter
																		
for file in "$@"; do
																		# Prüfen, ob das Arguemnt eine existierende Datei ist!
																		
	#Ingorieren von mp4 mit Warnung
	if [[ $file == *.mp4 ]]; then
		echo $file is already mp4
																		continue
	fi

	#Konvertieren von wmv in mp4
	if [[ $file == *.wmv ]]; then
		echo Converting $file to mp4
		newname=${filename::-3}											; newname=${file::-4}    # ZWEI(!) FEHLER!
																		# Haben Sie das nie ausprobiert?
																		# Außerdem: eigentlich eher basename als newname
		echo ffmpeg -i $file $newname.mp4
		#Abbruch wenn Fehler beim Konvertieren
		if [[ $? > 0 ]]; then
			echo Error with Converting
			exit 1
		fi
	fi
done

exit 0

                                                                        # Grundstruktur mit Schleife  OK
                                                                        # und shift über alle Parameter  OK
                                                                        # Dateinamen beim ffmpeg-Aufruf gequotet NO
                                                                        # Fehlermeldung / Hilfe beim Aufruf ohne Argument NO
                                                                        # 11_Rammstein.mp4 wird  nicht konvertiert. OK
                                                                        # mp4-Dateiname wird korrekt erzeugt. NO
                                                                        
                                                                        # 1.5 / 3
                                                                        
