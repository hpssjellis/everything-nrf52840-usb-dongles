/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe

 */



#include <ArduinoBLE.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include "utility/wifi_drv.h"
#include "arduino_secrets.h"


#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

// Global variables for button
const int ledPin = LED_BUILTIN; // set ledPin to on-board LED

BLEDevice myPeripheralOld ;




void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  
 // setupWifi();
  setupBle();
}





void loop() {
  
  Serial.print("Ble 1");
  myBLE();
  delay(2000);
  Serial.print("Ble 2");
  myBLE();
  delay(2000);
  Serial.print("Ble 3");
  myBLE();
  delay(2000);
  Serial.print("Ble 4");
  myBLE();
  delay(2000);
  Serial.print("NOW LETS TRY WIFI");
  myWifi();
  delay(10000);
}



void setupWifi(){
    // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 3 default 10 seconds for connection:
    delay(3000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
  
}



void setupBle(){
  
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


void myWifi(){  
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.print("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
       // Serial.write(c); tons of info done here
       
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
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


void myBLE(){

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

  
