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


5. Working on Wifi webpage that shows the BLE LED status



