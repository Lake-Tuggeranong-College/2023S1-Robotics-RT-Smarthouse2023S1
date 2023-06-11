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
#define CRASH_SENSOR 7

// Piezo Buzzer
#define PIEZO_PIN 8

// Traffic Lights - LED Outputs
#define LED_RED A0
#define LED_YELLOW A1 
#define LED_GREEN A2

const int DC_MOTOR = 7;

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
  pinMode(CRASH_SENSOR, INPUT);

  // Piezo Buzzer
  pinMode(PIEZO_PIN ,OUTPUT);

  // Traffic Lights - LED Outputs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  //DC Motor
  pinMode(DC_MOTOR, OUTPUT);
}

void loop() {

  /*int lineValue = digitalRead(LINE_SENSOR_PIN);
  Serial.print("Line = ");
  Serial.println(lineValue);

  int potValue = analogRead(POTENTIOMETER_PIN);
  Serial.print("Pot = ");
  Serial.println(potValue);

  int brightness = map(POTENTIOMETER_PIN, 0, 1023, 0, 255);  // Map the potentiometer value to LED brightness (0-255)

  analogWrite(ledPin, brightness);  // Set the LED brightness using PWM

  delay(10);  // Delay for stability

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
  */
}

void houseLockdown() {
  // Lock all doors
  // Activate security screens over windows
  digitalWrite(motorPin, HIGH);

  // Update state
  isHouseLockedDown = true;

  // Optional: Print message
  Serial.println("House lockdown activated!");
}

void activateAlertSystem() {
  // Activate LEDs
  digitalWrite(ledPin, HIGH);

  // Activate buzzers
  digitalWrite(buzzerPin, HIGH);

  // Update state
  isAlertSystemActivated = true;

  // Optional: Print message
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
