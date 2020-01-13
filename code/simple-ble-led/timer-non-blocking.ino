/*
  Timer

  non-blocking

 */


int myInterval=3000;  // 1000 = wait 1 second
unsigned long myOldTme=0;
const int ledPin = LED_BUILTIN; // set ledPin to on-board LED


void setup() {
  pinMode(ledPin, OUTPUT);
 
}


void loop() {
  unsigned long myNewTime = millis();
  if ((unsigned long)(myNewTime - myOldTme) >= myInterval) {
    myOldTme = myNewTime;      
    digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle the LED on Pin 13 most boards  
    
   }
}


