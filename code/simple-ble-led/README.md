Just got this working, Jan 6th, 2020






Live Demo at <a href="https://hpssjellis.github.io/everything-nrf52840-usb-dongles/code/simple-ble-led/index.html">https://hpssjellis.github.io/everything-nrf52840-usb-dongles/code/simple-ble-led/index.html</a>


Demo works for any LED READ/Write activated Bluetooth Low Energy device.

For Arduino Nano 33 BLE or Ble Sense or IOT the code below should work. (Note Pin4 to +3V3 volts should also activate the LED)

simple-led-peripheral.ino



To use a second Arduino to connect to the first arduino the code at should work. (Note: Send 1 to connect, send 2 to scan, once connected Pin2 to 3V3 should turn on the LED on both Arduinos. )

simple-led-central.ino









