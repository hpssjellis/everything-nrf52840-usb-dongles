/*
  Serial Show LED

  This example creates a BLE central service that communicates with 
  the simple-LED-myPeripheral button controlled LED. Printing out in the serial
  monitor any connected LED service that has the local name containg LED.
  LED flashes when trying to connect

  This example code is in the public domain.
  Edited By Jeremy Ellis
  Jan 2020

*/


#include <ArduinoBLE.h>

// Global variables for button
const int ledPin = LED_BUILTIN; // set ledPin to on-board LED

BLEDevice myPeripheralOld ;

void setup() {

  pinMode(ledPin, OUTPUT);           
  
  Serial.begin(9600);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  Serial.println("BLE Central - myPeripheral Explorer Rocksetta version 1.07");
  BLE.scan(); // start scanning for myPeripherals
  
}

void loop() {   // main loop
  updateBLE();
  delay(3000);
}

// helper function to print HEX variables
void printData(const unsigned char data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];
    if (b < 16) {
      Serial.print("0");
    }
    Serial.print(b, HEX);
  }
}


void updateBLE(){

  BLEDevice myPeripheral = BLE.available();

  if (myPeripheral) {

    //  if (myPeripheral.localName() == "LED") { //  use only if you know the exact name
    if (myPeripheral.localName().indexOf("LED") >= 0){ // contains name 
      BLE.stopScan();
      // connect to the myPeripheral
      Serial.println("Connecting ...");
      digitalWrite(ledPin, HIGH); // LED on
      if (myPeripheral.connect()) {
        Serial.println("Connected");
      } else {
        Serial.println("Failed to connect!");
        return;
      }

      // discover myPeripheral attributes
      Serial.println("Discovering attributes ...");
      if (myPeripheral.discoverAttributes()) {
        Serial.println("Attributes discovered");
      } else {
        Serial.println("Attribute discovery failed!");
        //myPeripheral.disconnect();
        return;
      }

      BLECharacteristic ledCharacteristic =   myPeripheral.characteristic("19b10011-e8f2-537e-4f6c-d104768a1214");
      // Note: Also works the 2 GATT's are slightly different: service=19b10010,  LED=19b10011
      // BLECharacteristic ledCharacteristic =   myPeripheral.service("19b10010-e8f2-537e-4f6c-d104768a1214").characteristic("19b10011-e8f2-537e-4f6c-d104768a1214");  //worked

      if (!ledCharacteristic) {
        Serial.println("myPeripheral does not have LED characteristic!");
        myPeripheral.disconnect();
        return;
      } else if (!ledCharacteristic.canWrite()) {
        Serial.println("myPeripheral does not have a writable LED characteristic!");
        myPeripheral.disconnect();
        return;
      }

      // check if the characteristic is readable
      if (ledCharacteristic.canRead()) {
        // read the characteristic value
        ledCharacteristic.read();
    
        if (ledCharacteristic.valueLength() > 0) {
          Serial.println();
          Serial.print(myPeripheral.localName());
          Serial.print("  0x");
          printData(ledCharacteristic.value(), ledCharacteristic.valueLength());
          // print out the value of the characteristic
          Serial.println(" HEX value: ");       
        }
      }

      Serial.println("myPeripheral disconnected");
      digitalWrite(ledPin, LOW);
      BLE.stopScan();
      myPeripheral.disconnect();
      BLE.scan();

    }
  }   // end  if (myperipheral)
}     // end updateBLE()

  
