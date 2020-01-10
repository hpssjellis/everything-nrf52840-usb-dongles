/*
  Simple-LED-Central

  This example creates a BLE central service that communicates with 
  the simple-LED-peripheral button controlled LED.

  This example code is in the public domain.
  Edited By Jeremy Ellis
  Jan 2020

  
*/


#include <ArduinoBLE.h>

// Global variables for button
const int ledPin = LED_BUILTIN; // set ledPin to on-board LED
const int buttonPin = 2;
int myOldButtonValue;

int myIncomingByte = 0;

BLEDevice peripheralOld ;

void setup() {

  pinMode(ledPin, OUTPUT);           
  pinMode(buttonPin, INPUT_PULLDOWN); // use button pin as an input
  
  Serial.begin(9600);
  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  Serial.println("BLE Central - Peripheral Explorer Rocksetta version 1.07");

  // start scanning for peripherals
  BLE.scan();
}

void loop() {

   updateBLE();

 //  updateBLE();

 // updateBLE();

  delay(3000);
}

void updateBLE(){
  
  // check if a peripheral has been discovered
  
     BLEDevice peripheral = BLE.available();


  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service


    // see if peripheral is a LED
  //  if (peripheral.localName() == "LED") { //  content.indexOf("Teststring") >= 0
    if (peripheral.localName().indexOf("LED") >= 0){ 
      // Only print if peripheral has LED in it's local name  
       BLE.stopScan();
       controlLed(peripheral);     
       Serial.println("Peripheral disconnected");
       BLE.stopScan();
     //  while (peripheral.connect()) {
          peripheral.disconnect();
      // }
       BLE.scan();

    }
  }
}




void printData(const unsigned char data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];
    if (b < 16) {
      Serial.print("0");
    }
    Serial.print(b, HEX);
  }
}






void controlLed(BLEDevice peripheral) {

  // connect to the peripheral
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }



  // discover peripheral attributes
  Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Attributes discovered");
  } else {
    Serial.println("Attribute discovery failed!");
    //peripheral.disconnect();
    return;
  }




    BLECharacteristic ledCharacteristic =   peripheral.characteristic("19b10011-e8f2-537e-4f6c-d104768a1214");
  // Note the 2 GATT's are slightly different: service=19b10010,  LED=19b10011
   // BLECharacteristic ledCharacteristic =   peripheral.service("19b10010-e8f2-537e-4f6c-d104768a1214").characteristic("19b10011-e8f2-537e-4f6c-d104768a1214");  //worked



  if (!ledCharacteristic) {
    Serial.println("Peripheral does not have LED characteristic!");
    peripheral.disconnect();
    return;
  } else if (!ledCharacteristic.canWrite()) {
    Serial.println("Peripheral does not have a writable LED characteristic!");
    peripheral.disconnect();
    return;
  }



    //  Serial.print("ledCharacteristic.uuid(): ");
  //Serial.println(ledCharacteristic.uuid());
  //Serial.print("ledCharacteristic.properties(): ");
  //Serial.println(ledCharacteristic.properties(), HEX);



  
 // Serial.println("if (ledCharacteristic.canRead())");

  // check if the characteristic is readable
  if (ledCharacteristic.canRead()) {
    // read the characteristic value
    ledCharacteristic.read();

    if (ledCharacteristic.valueLength() > 0) {
            Serial.println();
            Serial.print(peripheral.localName());
            Serial.print("  0x");
       printData(ledCharacteristic.value(), ledCharacteristic.valueLength());

  
      // print out the value of the characteristic
      Serial.println(" HEX value: ");
     // Serial.print(", value 0x");
     // Serial.print(ledCharacteristic.value()[ledCharacteristic.valueLength()], HEX);

     // sprintf(charVal, "%04X", testVal);
    //  Serial.println(charVal);
     //  char charVal[8];
     //  sprintf(charVal, "%09X", ledCharacteristic.value());
     //  Serial.println(charVal);
      

    
    
    
    }
  }


  




 



}

  
