// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.


//PIN ASSIGNMENTS
// SD Card - Confirm Pin
#define SD_PIN 10

// Line Sensor
#define LINE_SENSOR_PIN 3

//Potentiometer
#define POTENTIOMETER_PIN A3

// Crash Sensor / Button
#define CRASH_SENSOR_PIN 7

// Piezo Buzzer
#define PIEZO_PIN 8

// Traffic Lights - LED Outputs
#define LED_RED A0
#define LED_YELLOW A1 
#define LED_GREEN A2

const int DC_MOTOR_PIN_1 = 6;        // Replace with your motor pin 1
const int DC_MOTOR_PIN_2 = 7;        // Replace with your motor pin 2
const int MOTOR_SPEED = 255; 
int crashState = 0;
bool isLocked = false;


int potValue = 0;
int ledValue = 0;



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

  // Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("initialization done.");
  logEvent("System Initialisation...");

  // PINMODES
  // Line Sensor
  pinMode(LINE_SENSOR_PIN, INPUT);

  //Potentiometer
  pinMode(POTENTIOMETER_PIN, INPUT);

  // Crash Sensor / Button
  pinMode(CRASH_SENSOR_PIN, INPUT);

  // Piezo Buzzer
  pinMode(PIEZO_PIN ,OUTPUT);

  // Traffic Lights - LED Outputs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  //DC Motor
  pinMode(DC_MOTOR_PIN_1, OUTPUT);
  pinMode(DC_MOTOR_PIN_2, OUTPUT);




}

void loop() {

  crashState = digitalRead(CRASH_SENSOR_PIN);

  // If crash is detected, toggle the lock state
  if (crashState == HIGH) {
    if (!isLocked) {
      lockHouse();  // Lock the house
    } else {
      unlockHouse();  // Unlock the house
    }
    delay(200);  // Debounce delay (adjust as needed)
  }
}


// Function to control lights
void controlLights() {
  // Read potentiometer value
  potValue = analogRead(POTENTIOMETER_PIN);

  // Map potentiometer value to LED brightness range
  greenLedValue = map(potValue, 0, 1023, 0, 255);
  yellowLedValue = map(potValue, 0, 1023, 0, 180);
  redLedValue = map(potValue, 0, 1023, 0, 120);

  // Update LED brightness
  analogWrite(LED_GREEN, greenLedValue);
  analogWrite(LED_YELLOW, yellowLedValue);
  analogWrite(LED_RED, redLedValue);
}

// Function to lock the house
void lockHouse() {
  digitalWrite(DC_MOTOR_PIN_1, HIGH);
  digitalWrite(DC_MOTOR_PIN_2, LOW);
  delay(2000);  // Motor runs for 2 seconds (adjust as needed)
  digitalWrite(DC_MOTOR_PIN_1, LOW);
  isLocked = true;
}

// Function to unlock the house
void unlockHouse() {
  digitalWrite(DC_MOTOR_PIN_1, LOW);
  digitalWrite(DC_MOTOR_PIN_2, HIGH);
  delay(2000);  // Motor runs for 2 seconds (adjust as needed)
  digitalWrite(DC_MOTOR_PIN_2, LOW);
  isLocked = false;
}

void activateAlertSystem() {
  // Activate LEDs
  digitalWrite(LED_RED, HIGH);

  // Activate buzzers
  tone(PIEZO_PIN, 1000, 200);

  // Update state
  isAlertSystemActivated = true;

  // Print message
  Serial.println("Alert system activated!");
}

void resetSecuritySystem() {
  // Deactivate LEDs
  digitalWrite(ledPin, LOW);

  // Deactivate buzzers
  digitalWrite(buzzerPin, LOW);

  // Update state
  isAlertSystemActivated = false;
  isHouseLockedDown = false;

  // Optional: Print message
  Serial.println("Security system reset!");
}
