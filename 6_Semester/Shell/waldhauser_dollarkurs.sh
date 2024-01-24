#!/bin/bash

#Bearbeitung Aufgabe B.7 Luis Waldhauser

#Laden der Zeilen nach Informationen über Wechselkurs
dollar=$(lynx --dump https://markets.businessinsider.com/currencies/eur-usd | grep -A2 '(EUR - USD)') 

#Abbruch wenn Fehler Auftritt
if [[ $? > 0 ]]; then													# sehr gut
	echo Error with getting information
	exit 1
fi

#Ausgabe des Wechselkurses formatiert
echo $dollar | awk '{print substr($0, 50, length($0)-64 ) " $"}'		# Wow, da greifen Sie ganz schön in die awk-Trickkiste. Respekt.
																		# Aber: Das Abzählen von Buchstaben ist brandgefährlich, insbesondere 
																		# wenn es über mehrere Zeilen geht. Wesentlich besser wäre z.B.
																		echo "$dollar" | grep -E [0-9]+ | awk '{print $1 " $"}'

exit 0
																		# Gut gemacht.
																		# 2 / 2
