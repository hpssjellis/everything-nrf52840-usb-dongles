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
BLEDevice peripheral;
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


  
  // check if a peripheral has been discovered
  peripheral = BLE.available();



  if (Serial.available() > 0) {
     myIncomingByte = Serial.read(); // read the incoming byte:
     Serial.print(" I received:");
     Serial.println(myIncomingByte);

     // send '2' to reset scan
     if (myIncomingByte == 50){   // 50=2 in ascii, 10=carriage return
       BLE.stopScan();
       BLE.scan();
     }

     // send '1' to connect to last found device   
     if (myIncomingByte == 49){   // 49=1 in ascii, 10=carriage return

       BLE.stopScan();
       Serial.print("Trying to control LED: localName: ");     
       Serial.print(peripheralOld.localName());
       Serial.print(", address: ");
       Serial.print(peripheralOld.address());
       delay(5);
       Serial.clear();
       controlLed(peripheralOld);

     }



}




  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service


    // see if peripheral is a LED
  //  if (peripheral.localName() == "LED") { //  content.indexOf("Teststring") >= 0
    if (peripheral.localName().indexOf("LED") >= 0){ 
      // Only print if peripheral has LED in it's local name  

   if ( peripheralOld.address() != peripheral.address() ){

    
    Serial.print("Old.address()");
    Serial.print(peripheralOld.address());
    Serial.print(", New.address()");
    Serial.print(peripheral.address());
    Serial.println();
    
    peripheralOld = peripheral;
    
    Serial.print("Found LED containing local name: ");
    Serial.print(peripheral.localName());
    Serial.print(", address: ");
    Serial.print(peripheral.address());
    Serial.print(", UUID: ");
    Serial.print(peripheral.advertisedServiceUuid());
    
    Serial.print("  ");
    Serial.println();

     }
    }
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
    peripheral.disconnect();
    return;
  }


  // Note the 2 GATT's are slightly different: service=19b10010,  LED=19b10011
    BLECharacteristic ledCharacteristic =   peripheral.service("19b10010-e8f2-537e-4f6c-d104768a1214").characteristic("19b10011-e8f2-537e-4f6c-d104768a1214");  //worked
  
    Serial.print("ledCharacteristic: ");
    Serial.println(ledCharacteristic);

    Serial.print("ledCharacteristic: ");
    Serial.println(ledCharacteristic);
    
    Serial.print("ledCharacteristic.descriptor(0): ");
    Serial.println(ledCharacteristic.descriptor(0));
    
    Serial.print("ledCharacteristic.descriptor(0).value(): ");
    Serial.println((int)ledCharacteristic.descriptor(0).value());


  if (!ledCharacteristic) {
    Serial.println("Peripheral does not have LED characteristic!");
    peripheral.disconnect();
    return;
  } else if (!ledCharacteristic.canWrite()) {
    Serial.println("Peripheral does not have a writable LED characteristic!");
    peripheral.disconnect();
    return;
  }

  while (peripheral.connected()) {
    // while the peripheral is connected


  if (Serial.available() > 0) {
     myIncomingByte = Serial.read(); // read the incoming byte:
     Serial.print(" I received:");
     Serial.println(myIncomingByte);

     // send '2' to reset scan
     if (myIncomingByte == 50){   // 50=2 in ascii, 10=carriage return
       BLE.stopScan();
       peripheral.disconnect();
       BLE.scan();
     }
    }


  // Read button, compare and set button
  int myButtonValue = digitalRead(buttonPin);

  if (myOldButtonValue != myButtonValue){ 
    myOldButtonValue = myButtonValue; 
    digitalWrite(ledPin, myOldButtonValue);
    if (myButtonValue == 1){
      ledCharacteristic.writeValue((byte)0x01);   //ble led on
    } else{
      ledCharacteristic.writeValue((byte)0x00);  // ble led off
    }

  }



/*
    // read the button pin
    int buttonState = digitalRead(buttonPin);





    if (oldButtonState != buttonState) {
      // button changed
      oldButtonState = buttonState;

      if (buttonState) {
        Serial.println("button pressed");

        // button is pressed, write 0x01 to turn the LED on
        ledCharacteristic.writeValue((byte)0x01);
      } else {
        Serial.println("button released");

        // button is released, write 0x00 to turn the LED off
        ledCharacteristic.writeValue((byte)0x00);
      }
    }


*/

    
  }

  Serial.println("Peripheral disconnected");
}
