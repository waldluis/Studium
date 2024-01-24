#!/bin/bash

#Bearbeitung Aufgabe B.3 Luis Waldhauser

#Ausgabe des groessten Hauptspeichers in Gigabyte
#  findmnt -no size | head -1 | sed "s/[^0-9]//g"
																		# Was verstehen Sie denn unter "Hauptspeicher" ?
																		# Das ist RAM und nicht die Festplatte.

#Variable initialisieren
size=0

#Schreibt in Variable size die groesse des Hauptspeichers
function getStorageSize ()
{
	size=$(findmnt -no size | head -1 | sed "s/[^0-9]//g")
	return 0
	                                                                    # Nein! Nein! Nein! Eine Funktion arbeitet nicht mit globalen 
                                                                        # Variablen zur Rückgabe. Wer hat Ihnen das beigebracht?
}

#Aufruf der Funktion
getStorageSize
																		echo size=$size
																		
#Ausgabe des jeweiligen Kommentars
if (($size<2)); then
	echo Kinderrechner
elif (($size < 8)); then
	echo Standardrechner
elif (($size > 8)); then
	echo Profirechner
fi

exit 0
																		# 2 / 2
																		
