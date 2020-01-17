Just got this working, Jan 6th, 2020






Live Demo at <a href="https://hpssjellis.github.io/everything-nrf52840-usb-dongles/code/simple-ble-led/index.html">https://hpssjellis.github.io/everything-nrf52840-usb-dongles/code/simple-ble-led/index.html</a>


Demo works for any LED READ/Write activated Bluetooth Low Energy device.

For Arduino Nano 33 BLE or Ble Sense or IOT the code below should work. 

1. simple-led-peripheral.ino

(Note Pin4 to +3V3 volts should also activate the LED)



2. simple-led-central.ino


To use a second Arduino to connect to the first arduino the code should work. (Note: Send 1 to connect, send 2 to scan, once connected Pin2 to 3V3 should turn on the LED on both Arduinos. )



3. index.html

Webpage that allows BLE connections.


4. serial-show-LED.ino

In the serial monitor shows any BLE labelled with "LED" in the local name. Shows 0x00 if LED off 0x01 if LED on


5. klausWifiBle.ino

Awesome example by [Klaus_K](https://forum.arduino.cc/index.php?action=profile;area=showposts;u=1331775_K) of using a Nano 33 IoT to generate a webpage that then allows you to switch to BLE. The ble can be controlled by nrf-connect for mobile and switch back to the webpage. The web page also has easy to use buttons for turning the LED on and Off.


Thanks Klaus,  I made some minor changes to make your links into buttons.

https://forum.arduino.cc/index.php?topic=657710.0



6. wifi-ble-draft.ino

This is the now working, just needs a few touch ups. Expects a few BLE devices to be nearby
and setup with the Simple_LED.ino program. The names of the Simple-LED devices are very important as this version 
has the names pre-programmed.



7. wifi-ble-generic.ino

This does seem to be working, just having disconnect issues that I am working on. 2 arduino help forums about it

https://forum.arduino.cc/index.php?topic=657710.new;topicseen#new


https://forum.arduino.cc/index.php?topic=659164.0













