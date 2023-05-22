// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// SD Card - Confirm Pin
#define SDpin 53

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
    while (1)
      ;
  }


  // Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("initialization done.");
  logEvent("System Initialisation...");
}

void loop() {
  bluetoothConnectivity();
  motorDC();
  doorAlarm();
}

/*
  Reads distance value from Sonar (HC-SR04). 
  If less than threshold, activate Piezo buzzer
  @param None
  @return void
*/
void doorAlarm() {

}

/*
  Test Code for DC Motor Usage
  @param None
  @return void
*/
void motorDC() {

}

/*
  Print some information on the motor state in Serial Monitor
  @param None
  @return void
*/
void printSomeInfo()
{

}

/*
    Takes command entered from Bluetooth connection and executes functionality
    E.g. "1" - Write HIGH to builtin LED
    "0" - Write LOW to builtin LED
    @param bleCommand - string accepted from BLE Uart Connection
    @return void
*/
void bluetoothCommandReceived(String bleCommand) {

}

/*
    Handles BLE connectivity.
    Taken from library functionality.
    @param None
    @return void
*/
void bluetoothConnectivity() {

}

/*
    Log entries to a file on an SD card, and outputs to Serial Monitor
    @param dataToLog - string to save on SD card, timestamped.
    @return void
*/
void logEvent(String dataToLog) {


}
