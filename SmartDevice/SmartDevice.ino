// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// Servo
#include <Servo.h>
Servo myservo;

Servo securityServo;              // Servo object

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

// Sonar - HC-SR04
#define ECHO_PIN 6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define TRIG_PIN A4 //attach pin D3 Arduino to pin Trig of HC-SR04

const int DC_MOTOR_PIN_1 = 6;
const int DC_MOTOR_PIN_2 = 7;
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
  pinMode(PIEZO_PIN , OUTPUT);

  // Traffic Lights - LED Outputs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  //DC Motor
  pinMode(DC_MOTOR_PIN_1, OUTPUT);
  pinMode(DC_MOTOR_PIN_2, OUTPUT);

  // Sonar - HC-SR04
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT


}

void loop() {

  // Read crash sensor
  crashState = digitalRead(CRASH_SENSOR_PIN);
  // Read PIR sensor
  isPIRSensorTriggered = digitalRead(pirSensorPin);



  // If crash is detected, toggle the lock state
  if (crashState == HIGH) {
    if (!isLocked) {
      lockHouse();  // Lock the house
    } else {
      unlockHouse();  // Unlock the house
    }
    delay(200);  // Debounce delay
  }


  
  // Check for a parcel at the door
  bool isParcelPresent = isParcelAtDoor();

  if (isParcelPresent) {
    // Turn on the LED
    digitalWrite(LED_YELLOW, HIGH);
    Serial.println("Parcel detected at the door!");
  } else {
    // Turn off the LED
    digitalWrite(LED_YELLOW, LOW);
  }


  if (isPIRSensorTriggered && !isAlertSystemActivated) {
    activateAlertSystem();
  }

  // Control the security camera servo
  controlSecurityCamera();

  // Delay for a short period
  delay(100);

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
  delay(2000);  // Motor runs for 2 seconds
  digitalWrite(DC_MOTOR_PIN_1, LOW);
  isLocked = true;
}



// Function to unlock the house
void unlockHouse() {
  digitalWrite(DC_MOTOR_PIN_1, LOW);
  digitalWrite(DC_MOTOR_PIN_2, HIGH);
  delay(2000);  // Motor runs for 2 seconds
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
  digitalWrite(LED_RED, LOW);

  // Deactivate buzzers
  digitalWrite(PIEZO_PIN, LOW);

  // Update state
  isAlertSystemActivated = false;
  isHouseLockedDown = false;

  // Optional: Print message
  Serial.println("Security system reset!");
}

// Function to control the security camera servo
void controlSecurityCamera() {
  // Read the distance from the sonar sensor
  long duration, distance;
  digitalWrite(sonarTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonarTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonarTriggerPin, LOW);
  duration = pulseIn(sonarEchoPin, HIGH); // Measure the duration of the echo pulse
  distance = (duration / 2) / 29.1; // converts ultrasonic to distance in cm: 29.1 is approx. speed of sound in air per cm at room temp, dividing by 2 gets the 1 way travel time.

  // Adjust the position of the servo based on the distance
  int angle = map(distance, 0, 200, 0, 180);
  securityServo.write(angle);
}


// Function to check for a parcel at the door
bool isParcelAtDoor() {
  lineSensorValue = digitalRead(LINE_SENSOR_PIN);
  return lineSensorValue == LOW;
}
