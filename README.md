# thrx-radar-project

So ich hab jetzt die "Hardware" zusammengeschraubt und nun fehlt nur 
noch die Software :-)

Die Software besteht aus drei Anteilen:

* Radarauswertung
* Matrix Display
* Serial print zum debuggen

Jeder für sich funktioniert.

du kannst die anderen Teile ausblenden um nur einen Teil zu testen.
Serial Print ist auskommentiert.
--> Messung läuft und eine Zahl wird angezeigt

Das Radarsensor Projekt basiert auf
http://www.hjberndt.de/soft/radar/

Das Matrix Display auf Adafruit Beispielen:
https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/library


Folgende Probleme sind offen:
- Wenn man mehrere matrix.println oder auch die serial.print (ln) 
Befehle mit einbaut zeigt das Display einzelne farbige Punkte
- Wenn man den matrix.start() ausführt misst der Radarsensor viel höhere 
frequenzen als wenn er allein läuft.
Die Bibliotheken für das Matrix Display sind angeblich auch etwas 
hardwarenah programmiert, und daher nicht exakt kompatibel zu allem anderen.

Doku:
Hardware:
Arduino Uno
Geschwindigkeitssensor über 5V von Arduino versorgt
Ausgangssignal an A5 (Analog Eingang zum Aufzeichnen der Frequenz)
und an D11 für den Vortrigger ab einem bestimmten Signallevel

32x32 Matrix RGB Display

DC-DC-Wandler:
Stromversorgung 7-12V Eingang --> Direkt an Arduino Eingang angeschlossen.
Ausgang eingestellt auf 5V --> Display

-----------------------


PWM Einstellungen:
https://playground.arduino.cc/Main/TimerPWMCheatsheet


Technische Details:
http://sphinx.mythic-beasts.com/~markt/ATmega-timers.html

