// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RadarMatrix.h>

// If your 32x32 matrix has the SINGLE HEADER input,
// use this pinout:
#define CLK 8 // MUST be on PORTB! (Use pin 11 on Mega)
#define OE 9
#define LAT 10
#define A A0
#define B A1
#define C A2
#define D A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

/*
 Radar-Sensor RSM-1650 24 GHz
 Verstärkung ca. 60 dB
 Gibt die Geschwindigkeit v
 mit zwei Nachkommastellen aus,
 wenn 44 Hz 1 km/h entsprechen.
*/
#define TRIGGER_IN A5
#define TRIGGER_LEVEL 30 // 30 empfindlicher, 10 keine Reaktion
#define RADAR_IN 11
#define RADAR_OUT 13
#define SCANS 8
int trigger, vmax;
double v;
char velout[2]; //Ausgabe für 2-Stellige Geschwindigkeit

void setup()
{

    // Serial.begin(9600);
    // Serial.print("Program started\n"); // die serial Print befehle und zu viele matrix.println
  // befehle führen zu Punkten auf dem Display
  //  delay(2000);// Give reader a chance to see the output.

  pinMode(RADAR_IN, INPUT);
  pinMode(RADAR_OUT, OUTPUT);
  pinMode(TRIGGER_IN, INPUT);

  matrix.begin(); //Dieser Befehl lässt den Radarsensor falsch messen. Die Werte werden zu hoch

  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  // fix the screen with black
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  // draw a circle in yellow
  matrix.fillCircle(16, 16, 14, matrix.Color333(3, 3, 0));
  matrix.drawCircle(15, 20, 5, matrix.Color333(0, 0, 0));
  matrix.fillRect(10, 15, 11, 5, matrix.Color333(3, 3, 0));
  matrix.fillCircle(9, 9, 2, matrix.Color333(0, 0, 0));
  matrix.fillCircle(23, 9, 2, matrix.Color333(0, 0, 0));

  delay(2000); // 2 Sekunden
}

void loop()
{
  unsigned long T; // Periodendauer in us
  double f;        // Frequenz in MHz
  vmax = 0;        // Auf Integer gesetzt um Speicher und Rundung zu sparen

  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  do
  {
    trigger = analogRead(TRIGGER_IN);
    analogWrite(RADAR_OUT, map(trigger, 0, 1023, 0, 255));
  } while (trigger > TRIGGER_LEVEL);
  analogWrite(RADAR_OUT, 0);
  for (int i = 0; i < SCANS; i++) // 8 Messungen
  {
    T = pulseIn(RADAR_IN, HIGH) + pulseIn(RADAR_IN, LOW);
    f = 1 / (double)T;      // f=1/T
    v = ((f * 1e6) / 44.0); // 24 GHz Radar
    vmax = max(v, vmax);    // Schleppzeiger
                            //  Serial.println(v);

    // matrix.setCursor(0,0);    // start left, with 24 pixel shift to bottom
    // matrix.setTextSize(1);     // size 1 == 8 pixels high
    // matrix.fillScreen(matrix.Color333(0, 0, 0));
    // matrix.setTextColor(matrix.Color333(3,3,3));
    // matrix.println(i);
  }

  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(0, 0); // start at top left
  matrix.setTextSize(3);  // size 1 == 8 pixels high

  sprintf(velout, "%d", vmax);
  matrix.setTextColor(matrix.Color333(1, 5, 1));
  matrix.print(velout);

  matrix.setCursor(0, 24); // start left, with 24 pixel shift to bottom
  matrix.setTextSize(1);   // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(3, 3, 3));
  matrix.print(" km/h");

  delay(2000); // 2 Sekunden
}
