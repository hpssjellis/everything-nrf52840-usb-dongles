
/*
  simple-led-peripheral.ino

  This example creates a BLE peripheral with service that contains a
  characteristic to control an LED and another characteristic that
  represents the state of the button.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - Button connected to pin 4

  You can use a generic BLE central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
  Edited By Jeremy Ellis
  Jan 2020

Can use Simple-LED-Central To communicated with this.
  
*/


#include <ArduinoBLE.h>

// Global constants and variables
const int ledPin = LED_BUILTIN; // set ledPin to on-board LED
const int buttonPin = 4;        // set buttonPin to digital pin 4
int myOldButtonValue;

BLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214"); // create service

// allow remote device to read and write
BLEByteCharacteristic ledCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// create button characteristics
BLEByteCharacteristic buttonCharacteristic("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);


void setup() {
  
  pinMode(ledPin, OUTPUT);           
  pinMode(buttonPin, INPUT_PULLDOWN); // use button pin as an input

  // Note: No serial needing a line feed so this works with battery power.
  // just to prove it is running, flash LED twice, since no serial.
  digitalWrite(ledPin, HIGH);
  delay(400);
  digitalWrite(ledPin, LOW);
  delay(400);

  digitalWrite(ledPin, HIGH);
  delay(400);
  digitalWrite(ledPin, LOW);
  delay(400);

  // begin initialization
  if (!BLE.begin()) {

    digitalWrite(ledPin, HIGH);
    while (1);  // kills it here
  }

  // set the local name peripheral advertises
  BLE.setLocalName("SimpleLED");
  
  // set the service
  BLE.setAdvertisedService(ledService);

  // add both characteristics to the service
  ledService.addCharacteristic(ledCharacteristic);
  ledService.addCharacteristic(buttonCharacteristic);

  // add the service
  BLE.addService(ledService);

  // set default values
  ledCharacteristic.writeValue(0);
  buttonCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

}


void loop() {
  
  BLE.poll();  // poll for BLE events

  // Read button, compare and set button
  int myButtonValue = digitalRead(buttonPin);

  if (myOldButtonValue != myButtonValue){ 
    myOldButtonValue = myButtonValue; 
    digitalWrite(ledPin, myOldButtonValue);
  }

  // Check if external program controlling button
  else if (ledCharacteristic.written()){
    digitalWrite(ledPin, ledCharacteristic.value());
  }

  delay(10); 
  
}
