#!/bin/bash

#Bearbeitung Aufgabe B.4 Luis Waldhauser

#Fehler wenn falsche Anzahl an Parameter
if (($# != 1)); then													# [[ ... ]]   ist üblicher.
	echo Falsche Anzahl an Argumenten
	exit 1
fi

seitenlaenge=$1

#Funktion für Ausgabe von bestimmter Anzahl an Sternen in einer Zeile
function sterneZeile ()
																		# Globale Variablen sind hier nicht schön.
{
	for ((i = 0; i < $(($1)); i++)); do									# Warum "$(($1))" und nicht "$seitenlaenge" ???
		printf "*"
	done
	printf "\n"
}

#Erste Zeile ausgeben
sterneZeile $seitenlaenge

#Zeilen mit * am Anfang und Ende mit Leerzeichen dazwischen ausgeben
for ((i = 0; i < ($(($1))/2)-1; i++)); do
	printf "*"
	for((j = 0; j < $(($1))-2; j++)); do
		printf " "
	done
	printf "*\n"
done

#Letzte Zeile ausgeben
sterneZeile $seitenlaenge

exit 0
																		# 3 / 3
