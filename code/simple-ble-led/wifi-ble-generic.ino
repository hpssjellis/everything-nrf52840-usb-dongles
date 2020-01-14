/*
  WiFi BLE Server

 A simple web server that shows the value of the analog input pins
 shuts down and loads BLE to identify knone LED BLE active devices
 then restarts Wifi before the page refreshes.

expects several prenamed Simple LED devices to be nearby and fresh running
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 
 modified Jan 14th, 2020
 by Jeremy Ellis
 Twitter @rocksetta
 */



#include <SPI.h>
#include <WiFiNINA.h>
#include "utility/wifi_drv.h"
#include "arduino_secrets.h"

#include <ArduinoBLE.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)


// Dynamic Global Variables
int myWifiInterval = 40000;       // 40 seconds
int myBleInterval = 6000;         // 6 seconds
const int myMaxArray = 10;        // no idea how many BLE devices
int myWebPageRefresh = 10;        // seconds for webpage to refresh, set really large for static website

//Regular Global Variables
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
int myInterval = myWifiInterval;  // 1000 = wait 1 second
unsigned long myOldTme=0;
const int ledPin = LED_BUILTIN;   // set ledPin to on-board LED
bool myChooseWifi = true;
bool myBleActive[myMaxArray];     // not pre-defined as false
String myBLENames[myMaxArray];
const uint8_t* myLedValue[myMaxArray];
WiFiServer server(80);

void setup() {
  pinMode(ledPin, OUTPUT);
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
  
  setupWifi();

  
    Serial.println("Need several BLE devices running Simple-LED");
    Serial.print("Wifi runs for: ");
    Serial.print(myWifiInterval/1000);
    Serial.print(" seconds, BLE runs for: ");
    Serial.print(myBleInterval/1000);
    Serial.println(" seconds.");

}





void loop() {


  if (myChooseWifi){
    myWifi();
  } else { // Do BLE
    updateBLE(); 
  }
  unsigned long myNewTime = millis();
  if ((unsigned long)(myNewTime - myOldTme) >= myInterval) {
    myOldTme = myNewTime;      
    digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle the LED on Pin 13 most boards  
    if (myChooseWifi) {  // shut off wifi turn on BLE
      myInterval = myBleInterval;  // 6 seconds
      myChooseWifi = false;
      Serial.println("shutting down Wifi");  
      WiFi.end();
      delay(2000); 
      Serial.println("Starting BLE"); 
      myBleActive[0] = false;
      myBleActive[1] = false;
      myBleActive[2] = false;
      myBleActive[3] = false;
      BLE.begin();
      BLE.scan(); 
    } else { // shut off BLE turn on Wifi
      myChooseWifi = true;
      myInterval = myWifiInterval; // 40 seconds
      Serial.println("Shutting down BLE");
      BLE.stopScan();
      BLE.end();
      delay(2000);
      Serial.println("Starting Wifi");
      // Re-initialize the WiFi driver
      // This is currently necessary to switch from BLE to WiFi
      // wiFiDrv.wifiDriverDeinit();
      // wiFiDrv.wifiDriverInit();
      status = WiFi.begin(ssid, pass);
      server.begin();
      Serial.print("Wifi Status: ");
      Serial.println(status); 
    }
    
   }  // end timer

}    // end void loop()

////////////////////////////////// Wifi stuff //////////////////

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



void myWifi(){  
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
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
          client.print("Refresh: ");           
          client.println(myWebPageRefresh);    // refresh the page automatically every x seconds, set to zero to stop? 
          
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

          client.print("<br><br><table border=1>");
          client.print("<tr>  <th>#</th>  <th>Active</th>  <th>LED</th>  <th>Name</th>  </tr>");

          for (int BleLoop = 0; BleLoop < myMaxArray; BleLoop++) {     
            client.print("<tr><td>");
            client.print(BleLoop);   
            if (!myBleActive[BleLoop]){  // check if not active
               client.print("</td>  <td>Not Active</td>  <td>...</td>  <td>"); 
            } else {
              if (ledIsOn(myLedValue[BleLoop])){
                 client.print("</td>  <td>Active</td>  <td>On</td>  <td>");              
              } else {
                 client.print("</td>  <td>Active</td>  <td>Off</td>  <td>");    
              }
            }
            client.print(myBLENames[BleLoop]);  
            client.println("</td></tr>");     
          }   // end for loop
    
          client.println("</table><br />"); 
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
  Serial.print("Load web browser at this IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}



////////////////////////////////// end Wifi ////////////////////

///////////////////////////// BLE stuff ////////////////////////









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



bool ledIsOn(const unsigned char data[]) {
  for (int i = 0; i < 1; i++) {
    unsigned char b = data[i];
    if (b <= 0) {
      return false;
    } else {
      return true;
   }
  }
}




/*
bool ledIsOn(const unsigned char data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];
    if (b <= 0) {
      return false;
    } else {
      return true;
   }
  }
}

*/





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
          Serial.print("value-length: ");
          Serial.print(ledCharacteristic.valueLength());
          Serial.print(", LocalName: ");
          Serial.print(myPeripheral.localName());
          Serial.print("  0x");
          printData(ledCharacteristic.value(), ledCharacteristic.valueLength());
          // print out the value of the characteristic
          Serial.println(" HEX value: "); 

////////////////////////////////// Start BLE Analysis  /////////////////////////////////////////////////////////////


          bool myBleIsStored = false;
          int myStoredLocation;
          for (int BleLoop2 = myMaxArray-1; BleLoop2 >= 0 ; BleLoop2--) { // count down and check if BLE device is already saved
            if (myPeripheral.localName() == myBLENames[BleLoop2]){
              myBleIsStored = true;
             }
            if (myBLENames[BleLoop2] == ""){  // if the name is missing then a new name can go there
               myStoredLocation = BleLoop2; 
            } 
          }
          if (!myBleIsStored){
            myBLENames[myStoredLocation] = myPeripheral.localName();  // save it if not saved
          }

          //regular loop here
          for (int BleLoop = 0; BleLoop < myMaxArray; BleLoop++) { 
            if (myPeripheral.localName() == myBLENames[BleLoop]){   
              Serial.println();
              Serial.print(myBLENames[BleLoop]);
              Serial.println();
              myBleActive[BleLoop] = true; 
              myLedValue[BleLoop] = ledCharacteristic.value();
              } 
          }





////////////////////////////////// End BLE Analysis  /////////////////////////////////////////////////////////////                
        }   // end ledChaaracteristic
      }

      Serial.println("myPeripheral disconnected");
      digitalWrite(ledPin, LOW);
      BLE.stopScan();
      myPeripheral.disconnect();
      BLE.scan();

    }
  }   // end  if (myperipheral)
}     // end updateBLE()

  
