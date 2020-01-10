/*
  BLE2WiFi

  This example creates a BLE peripheral with a service that contains a
  characteristic to switch to WiFi.

  The circuit:
  - Arduino Nano 33 IoT,

  You can use a generic BLE central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include "utility/wifi_drv.h"
#include "arduino_secrets.h"


#define BLE_UUID_NETWORK_CONFIG_SERVICE              "343D2964-5ECF-2297-4463-609011571F24"
#define BLE_UUID_NETWORK_ENABLE_CHARACTERISTIC       "767B22E7-EA6C-B017-286A-55B68310FD9D"

BLEService networkConfigService( BLE_UUID_NETWORK_CONFIG_SERVICE );
BLEBoolCharacteristic networkEnableCharacteristic( BLE_UUID_NETWORK_ENABLE_CHARACTERISTIC , BLERead | BLEWrite );

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssidName[] = SECRET_SSID;
char ssidPass[] = SECRET_PASS;

WiFiServer server( 80 );
int status = WL_IDLE_STATUS;
bool networkInitialized = false;
bool wifiModeFlag = false;

const int LED_PIN = LED_BUILTIN;

void setup()
{
  Serial.begin( 9600 );
  while ( !Serial );

  pinMode( LED_PIN, OUTPUT );
}

void loop()
{
  if( !networkInitialized )
  {
    if( !wifiModeFlag )
    {
      Serial.print( "Switch to BLE: " );
      if( !switch2BleMode() )
      {
        Serial.println( "failed" );
      }
      else
      {
        networkInitialized = true;
        Serial.println( "success" );
      }
    }
    else
    {
      Serial.print( "Switch to WiFi: " );
      if( !switch2WiFiMode() )
      {
        Serial.println( "failed" );
      }
      else
      {
        networkInitialized = true;
        Serial.println( "success" );
      }
    }
  }
  else
  {
    if( !wifiModeFlag )
    {
      bleMode();
    }
    else
    {
      wifiMode();
    }
  }
}


void bleMode()
{
  BLEDevice central = BLE.central();

  if ( central )
  {
    Serial.print( "Connected to central: " );
    Serial.println( central.address() );

    while ( central.connected() )
    {
      if( networkEnableCharacteristic.written() )
      {
        networkInitialized = false;
        wifiModeFlag = true;
        return;
      }
    }
  }
}


void wifiMode()
{
  int connectCount = 0;

  if ( status != WL_CONNECTED )
  {
    while ( status != WL_CONNECTED )
    {
      connectCount++;
      Serial.print( "WiFi attempt: " );
      Serial.println( connectCount );

      if( connectCount > 10 )
      {
        networkInitialized = false;
        wifiModeFlag = false;
        Serial.println( "WiFi connection failed" );
        return;
      }
      Serial.print( "Attempting to connect to SSID: " );
      Serial.println( ssidName );

      status = WiFi.begin( ssidName, ssidPass );

      if( status != WL_CONNECTED )
      {
        // wait 10 seconds for connection:
        delay( 10000 );
      }
    }
    printWiFiStatus();

    server.begin();
  }
  else
  {
    WiFiClient client = server.available();

    if ( client )
    {
      String currentLine = "";
      while ( client.connected() )
      {
        if ( client.available() )
        {
          char c = client.read();
          if ( c == '\n' )
          {
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if ( currentLine.length() == 0 )
            {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println( "HTTP/1.1 200 OK" );
              client.println( "Content-type:text/html" );
              client.println();

              // the content of the HTTP response follows the header:
              client.print( "Click <a href=\"/H\">here</a> turn the LED on<br>" );
              client.print( "Click <a href=\"/L\">here</a> turn the LED off<br><br>" );
              client.print( "Click <a href=\"/B\">here</a> disconnect WiFi and start Bluetooth<br>" );

              // The HTTP response ends with another blank line:
              client.println();
              break;
            }
            else        // if you got a newline, then clear currentLine:
            {
              if ( currentLine.startsWith( "GET /H" ) )
              {
                digitalWrite( LED_PIN, HIGH );
              }
              if ( currentLine.startsWith( "GET /L" ) )
              {
                digitalWrite( LED_PIN, LOW );
              }
              if ( currentLine.startsWith( "GET /B" ) )
              {
                // GET /B switch to Bluetooth
                networkInitialized = false;
                wifiModeFlag = false;
              }
              currentLine = "";
            }
          }
          else if ( c != '\r' )
          {
            currentLine += c;
          }
        }
      }
      client.stop();
    }
  }
}

bool switch2BleMode()
{
  if ( !BLE.begin() )
  {
    return false;
  }

  // set advertised local name and service UUID:
  BLE.setDeviceName( "Arduino Nano 33 IoT" );
  BLE.setLocalName( "Arduino Nano 33 IoT" );
  BLE.setAdvertisedService( networkConfigService );

  // add the characteristic to the service
  networkConfigService.addCharacteristic( networkEnableCharacteristic );

  // add service
  BLE.addService( networkConfigService );

  // set the initial value for the characeristic:
  networkEnableCharacteristic.writeValue( false );

  BLE.advertise();

  return true;
}


bool switch2WiFiMode()
{
  BLE.stopAdvertise();
  BLE.end();

  status = WL_IDLE_STATUS;

  // Re-initialize the WiFi driver
  // This is currently necessary to switch from BLE to WiFi
  wiFiDrv.wifiDriverDeinit();
  wiFiDrv.wifiDriverInit();

  return true;
}

void printWiFiStatus()
{
  Serial.print( "SSID: " );
  Serial.println( WiFi.SSID() );

  IPAddress ip = WiFi.localIP();
  Serial.print( "IP address: " );
  Serial.println( ip );

  long rssi = WiFi.RSSI();
  Serial.print( "Signal strength (RSSI):" );
  Serial.print( rssi );
  Serial.println( " dBm" );
}
