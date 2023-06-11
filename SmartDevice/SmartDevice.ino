// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// SD Card - Confirm Pin
#define SD_PIN 10

// Line Sensor
#define LINE_SENSOR_PIN 3

//Potentiometer
#define POTENTIOMETER_PIN A3

// Crash Sensor / Button
#define CRASH_SENSOR 7

// Piezo Buzzer
#define PIEZO_PIN 8

// Traffic Lights - LED Outputs
#define LED_RED A0
#define LED_YELLOW A1 
#define LED_GREEN A2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);  // wait for serial port to connect. Needed for native USB port only
  }

  // SD Card initialisation
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_PIN)) {
    Serial.println("initialization failed!");
    while (1);
  }
  //test

  // Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("initialization done.");
  logEvent("System Initialisation...");


  // Line Sensor
  pinMode(LINE_SENSOR_PIN, INPUT);

  //Potentiometer
  pinMode(POTENTIOMETER_PIN, INPUT);

  // Crash Sensor / Button
  pinMode(CRASH_SENSOR, INPUT);

  // Piezo Buzzer
  pinMode(PIEZO_PIN ,OUTPUT);

  // Traffic Lights - LED Outputs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {

  int lineValue = digitalRead(LINE_SENSOR_PIN);
  Serial.print("Line = ");
  Serial.println(lineValue);

  int potValue = analogRead(POTENTIOMETER_PIN);
  Serial.print("Pot = ");
  Serial.println(potValue);

  bool isCrashDetected = digitalRead(CRASH_SENSOR);

  if (isCrashDetected) {
    Serial.println("Crash detected: true");
  } else {
    Serial.println("Crash detected: false");
    tone(PIEZO_PIN, 1000, 200);
  }

  if (lineValue == 0) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  } else{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
  }


  delay(250);
}
