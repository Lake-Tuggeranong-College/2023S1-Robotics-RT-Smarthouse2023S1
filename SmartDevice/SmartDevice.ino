// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// SD Card - Confirm Pin
#define SDpin 10

//Potentiometer
#define POTENTIOMETER_PIN A3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);  // wait for serial port to connect. Needed for native USB port only
  }

  // SD Card initialisation
  Serial.print("Initializing SD card...");
  if (!SD.begin(SDpin)) {
    Serial.println("initialization failed!");
    while (1);
  }


  // Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("initialization done.");
  logEvent("System Initialisation...");


  //Potentiometer
  pinMode(POTENTIOMETER_PIN, INPUT);
}

void loop() {

  int potValue = analogRead(POTENTIOMETER_PIN);
  Serial.println(potValue);
}

void runPot() {
  
}

/*
  Reads distance value from Sonar (HC-SR04). 
  If less than threshold, activate Piezo buzzer
  @param None
  @return void
*/
void doorAlarm() {
  
}
