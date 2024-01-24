#!/bin/bash

#Bearbeitung Aufgabe B.5 Luis Waldhauser

#Startwert experimentell hochgesetzt um Laufzeit zu verringern
#Start bei 0 möglich, dauert ewig
                                                                        # Dann tun Sie etwas dagegen!
                                                                        # Das es sich um einen Überlauf handelt, haben Sie ja erkannt.
                                                                        # Der überlauf hängt mit der Zahl der Bits zusammen.
                                                                        # Damit können Sie den Wert immer verdoppeln.
x=9223372036854700000

#Schleife zählt hoch bis Ueberlauf
#Wenn Ueberlauf Abbruch und Ausgabe der Zahl
while true; do
    if ((x<0)); then
        break
    fi
    MAX_INT=$x
                                                                        # Please mind that by convention, only environment variables are written
                                                                        # in UPPERCASE while shell variables usually have lowercase names
    x=$((x+1))
done

echo MAXINT: $MAX_INT
exit 0
                                                                        # 1 /2 P.
