
// Default Nano33BLE
//#define LED_BUILTIN  P0_13  // Default (13u) P0_13
//#define A0 P0_4             // Default A0 = P0_4


// Makerdiary nRF52840 USB Dongle
//#define LED_BUILTIN  P0_24  //  P0_23 RED LED, P0_24 BLUE LED    
//#define A0 P0_2             //  A0 P0_2        

// Nordic nRF52840 USB Dongle
#define LED_BUILTIN  P0_6  //  P0_6 Green LED, P0_8 RED LED    
#define A0 P0_2             //  A0 P0_2   not really sure      


// Particle Argon Xenon probably similar.
//#define LED_BUILTIN  P1_12  //  D7 board LED   P1_12 
//#define A0 P0_3             //   A0 P0_3        



void setup(){  
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
}


void loop() {

  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.print("blink4 fast, A0 Voltage: --> ");
  Serial.println(voltage);

  
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);    
  delay(100);                    

  
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);    
  delay(100);                    
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);    
  delay(3000);                     
}
