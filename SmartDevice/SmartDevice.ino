// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// Servo
#include <Servo.h>

Servo securityServo; // Servo object

// PIN ASSIGNMENTS
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
#define ECHO_PIN 6 
#define TRIG_PIN A4

// PIR sensor
#define PIR_SENSOR_PIN 4

// variables for house lockdown proccess
const int DC_MOTOR_PIN_1 = 6;
const int DC_MOTOR_PIN_2 = 7;
const int MOTOR_SPEED = 255;
int crashState = 0;
bool isLocked = false;

// variables for lighting control
int potValue = 0;
int greenLedValue = 0;
int yellowLedValue = 0;
int redLedValue = 0;

// variables for the alert system
bool isPIRSensorTriggered = false;
bool isAlertSystemActivated = false;
bool isHouseLockedDown = false;

// variables for package detection
int lineSensorValue = 0;


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
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 

}

void loop() {

  // Read crash sensor
  crashState = digitalRead(CRASH_SENSOR_PIN);
  // Read PIR sensor
  isPIRSensorTriggered = digitalRead(PIR_SENSOR_PIN);



  // If crash detector is activated, toggle the house lockdown state by using lockHouse() and unlockHouse() functions
  if (crashState == LOW) {
    if (!isLocked) {
      lockHouse();  // Lock the house
    } else {
      unlockHouse();  // Unlock the house
    }
  }


  // Check for a parcel at the door by using value from isParcelAtDoor() function
  bool isParcelPresent = isParcelAtDoor();
  if (isParcelPresent) {
    // Turn on the LED
    digitalWrite(LED_YELLOW, HIGH);
    Serial.println("Parcel detected at the door!");
  } else {
    // Turn off the LED
    digitalWrite(LED_YELLOW, LOW);
  }

  // uses the activateAlertSystem() fuction if PIR sensor is triggered and the alert system is not already activated
  if (isPIRSensorTriggered && !isAlertSystemActivated) {
    activateAlertSystem();
  }

  // Control the security camera servo
  controlSecurityCamera();

  // Delay for a short period
  delay(100);
}



void controlLights() {
  /*
     Controls the brightness of LED's using the potentiometer
     to adjust the values.
     Didnt work fully as intended
     @param: none
     @return: void
  */
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




void lockHouse() {
  /*
     Activates dc motor to spin for 2 seconds and then stop.
     Worked as intended
     @param: none
     @return: void
  */
  digitalWrite(DC_MOTOR_PIN_1, HIGH);
  digitalWrite(DC_MOTOR_PIN_2, LOW);
  delay(2000);  // Motor runs for 2 seconds
  digitalWrite(DC_MOTOR_PIN_1, LOW);
  isLocked = true;
}



void unlockHouse() {
  /*
     Activates dc motor to spin in opposite direction for 2
     seconds then stop.
     Worked as intended
     @param: none
     @return: void
  */
  digitalWrite(DC_MOTOR_PIN_1, LOW);
  digitalWrite(DC_MOTOR_PIN_2, HIGH);
  delay(2000);  // Motor runs for 2 seconds
  digitalWrite(DC_MOTOR_PIN_2, LOW);
  isLocked = false;
}



void activateAlertSystem() {
  /*
     Activates the red LED and the piezo
     Worked as intended
     @param: none
     @return: void
  */
  
  // Activate LEDs
  digitalWrite(LED_RED, HIGH);

  // Activate buzzers
  tone(PIEZO_PIN, 1000, 200);

  // Update state
  isAlertSystemActivated = true;

  // Print message
  Serial.println("Alert system activated!");
}


void controlSecurityCamera() {
  /*
     Controls servo angle based off of the distance that the
     sonar detects an object from itself
     Didnt work as intended
     @param: none
     @return: void
  */
  
  // Read the distance from the sonar sensor
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH); // Measure the duration of the echo pulse
  distance = (duration / 2) / 29; // converts ultrasonic to distance in cm: 29 is approx. speed of sound in air per cm at room temp, dividing by 2 gets the 1 way travel time.

  // Adjust the position of the servo based on the distance
  int angle = map(distance, 0, 200, 0, 180);
  securityServo.write(angle);
}


bool isParcelAtDoor() {
  /*
     Detects whether there is anything activating the line
     sensor and returns the value "LOW" if there is.
     Worked succesfully
     @param: none
     @return: lineSensorValue
  */
  lineSensorValue = digitalRead(LINE_SENSOR_PIN);
  return lineSensorValue == LOW;
}
