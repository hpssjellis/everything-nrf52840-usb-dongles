# Everything About the nRF52840 USB Dongles
Anything I can find about the various nrf52840 (either with USB cables or direct plugin dongles) by Nordic, Arduino, Adafruit, Sparkfun, MakerDiary and others


Update: Jan 22, 2020

Making some headway here

https://community.platformio.org/t/like-if-you-have-an-nrf52840-nordic-usb-dongle-arduino-nano-33-ble-adafruit-sparkfun-april-makerdairy-fanstel-particle-or-any-other/11112/9


and here

https://community.platformio.org/t/same-bootloader-same-softdevice-different-board-different-pins/11411/2

Looks like the Nano 33 BLE defines pins from P0_00  right up to P1_15 directly from the nRF52840 SOC, which should make using the Nano33BLE bootloarder on other boards much easier to work with.



Created Dec 7th, 2019


  
# Big Picture
I want to make the best high school robotics program. 

1. I have already finished and student tested for 3 years a wifi based Robotics program Github at: [particle.io-photon-high-school-robotics](https://github.com/hpssjellis/particle.io-photon-high-school-robotics)  With Sensors, Actuators, web control, SPI, I2C, uArt and websockets. 

2. [A Machine Learning Javascript Tensorflow.js Program](https://www.rocksetta.com/tensorflowjs/). 

3. A cryptocurrency internet of things program using IOTA and a microcontroller. My hackster [here](https://www.hackster.io/jeremy-ellis/particle-photon-pay-iota-to-read-sensors-edb7b8). Waiting for IOTA software to mature. Githubs: [iota-community](https://github.com/iota-community)

4. Now I need to update my high school course to include [BLE](https://en.wikipedia.org/wiki/Bluetooth_Low_Energy) and [Openthread](http://openthread.io), but which boards to purchase?





# Basic Concept

The [Nordic nRF52840 SOC](https://www.nordicsemi.com/Products/Low-power-short-range-wireless/nRF52840) is getting a lot of publicity for it's great BLE (Bluetooth Low Energy) abilities and has been embedded in many boards from Nordic, Particle, Fanstel, Adafruit, Sparkfun, MakerDiary and Arduino. 


# The Problem

All the above companies that use the nRF52840 SOC embedded boards have their own technique for programming the boards, making it very difficult to pick and choose the product combination that works well in the classroom. Luckily, Arduino has just entered the race with their new Nano 33 BLE. That brings a huge community of capable hobbyists and professional engineers to the issue.  





  
# My (our) Solution

I would like to see how many of these boards we can get working on both the Nordic and Arduino platforms. Then I can choose which boards to include in my new version of my high school robotics course. Any help would be appreciated


# IDE Working Tutorials Chart 
updated Dec 8th 2019. Please send an issue or PR if you can replace any of the "not sure" with a link. Thanks in Advance. 

|  | Nordic nrf52840 USB Dongle| Arduino Nano 33 BLE| Adafruit Feather nrf52840| Particle Xenon|Sparkfun Pro nRF52840 Mini|
| --- | --- | --- | --- | --- | --- |
|**[Arduino IDE](https://www.tutorialspoint.com/arduino/arduino_installation.htm)**    |   not sure | [yes](https://www.arduino.cc/en/Guide/NANO33BLE) | [yes](https://learn.adafruit.com/introducing-the-adafruit-nrf52840-feather/arduino-bsp-setup) | [yes, needs j-link](https://medium.com/home-wireless/using-segger-studio-and-nordic-sdk-with-particle-xenon-91e34aeb632a) | [yes, few adjustements](https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython/all)  |
|**[Nordic nrf-connect for desktop](https://www.novelbits.io/nrf52840-usb-dongle-tutorial-1/)**  | [yes](https://www.novelbits.io/nrf52840-usb-dongle-tutorial-1/) | not sure | not sure | not sure | not sure  |
|**Run Nordic-SDK examples somehow**| not sure | [yes, issues, best to have a j-link](https://forum.arduino.cc/index.php?topic=649008.msg4392009#msg4392009) | not sure | not sure | [advanced-development-with-the-nrf5-sdk](https://learn.sparkfun.com/tutorials/nrf52840-advanced-development-with-the-nrf5-sdk)  |
|**Run Arduino Examples using Nordic nrf-connect for desktop** | not sure| not sure| not sure | not sure | not sure  |
|**[www.platformio.org](https://platformio.org/)** | not sure but has potential | not sure but has potential|  Yes have not tested | Yes have not tested | not sure but has potential  |
|**[my Gitpod of Openthread](https://github.com/hpssjellis/my-gitpod-of-openthread)** | yes download to nrf-connect for desktop| not sure but has potential| not sure but has potential | not sure | not sure but has potential  |



Note: Easiest approach would be to get the Nordic dongle working on the Arduino platform, but I have had some issues doing the opposite with the Nano 33 BLE getting it to load Nordic SDK examples. It does work but it is a bit flaky and I am not yet sure of all pin assignments. (I bricked my Nano 33 BLE Sense and need a j-link to fix it). Best to see if I can get some of these boards working fully on both platforms.

# Present thinking: 

I think I should use the Nordic board for basic BLE, Arduino Nano 33 BLE Sense board for most sensory work. Still wondering how to connect Wifi to these boards for the occassional diagnostics when needed.
1. Use the $18 USD [Arduino Nano 33 IOT](https://store.arduino.cc/usa/nano-33-iot) which has wifi but only bluetooth 4.2 but that should be compatible, except for long range BLE. Something I read is that both Radios can not operate at the same time, not sure if that is going to be a problem.
2. Use $20.00 USD [ESP8266](https://www.adafruit.com/product/3213) stacking Adafruit feather for Wifi support on whichever board I finally use or something with the $22.00 USD [ESP32](https://www.adafruit.com/product/3619) also with stacking feather form factor.
3. Use the Adafruit $27 USD [Particle Argon](https://www.adafruit.com/product/2721), which has both the nRF52840 and ESP32 modules but might be very difficult to program without the Particle pay per use Cloud. However I just found the Adafruit [Debugger](https://www.adafruit.com/product/4001) and since it is supported by Adafruit it might allow better access to this board. [Adafruit Steps here](https://learn.adafruit.com/circuitpython-on-the-nrf52/build-flash-particle). LIke the segger edu this debugger is just a type of j-link with the correct connector for the particle boards.
4. Any new board coming out with the nRF52840 and Wifi?

.




# Important links

For pinout comparison chart    [pinout-comparison-chart.md](pinout-comparison-chart.md)


My Openthread and Nordic SDK Online Browser compatible Docker. (Yes it is amazing).  [My Gitpod Github Openthread](https://github.com/hpssjellis/my-gitpod-of-openthread) This takes a very long time to build from scratch. First try the snapshot below, it takes less time to load. This snapshot was generated on Dec 4th, 2019 updated with the Nordic sdk. (Note: These are very confusing platforms if you are not use to either OpenThread or the Nordic SDK's. I will eventually simplify these for classroom use.)


[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io#snapshot/e709c382-8574-4775-876c-002bfeecc374)



For random links used while making this site    [random-links.md](random-links.md)



.



.



# The different Boards

Note: The dongle can plug directly into a computer USB port. They can also be powered by Cell phone chargers. The boards that need a USB cable are not necessarily better or worse they just need the cable. Both types can also be powered by an outside power source with varing levels of acceptable voltages. (Worth looking into, I know the Nano 33 BLE has some interesting features here, I think it can be powered by a 12 V battery. Better check)

## Nordic 
$10.00 USD [nRF52840 USB Dongle](https://www.digikey.com/product-detail/en/nordic-semiconductor-asa/NRF52840-DONGLE/1490-1073-ND/9491124?_ga=2.112542724.1204958722.1575703702-701218832.1573252054&_gac=1.12604485.1574457358.Cj0KCQiAq97uBRCwARIsADTziyako1nHRHIJGlUf6ZprMFUFuqiaruXRiJ3sGP4mQ3FC3kIQmQxaQZsaAswzEALw_wcB)

The best, but most confusing set of examples are at the [Nordic NRF5 SDK](https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK/Download). 

Community: [Nordic Dev Zone](https://devzone.nordicsemi.com/) These guys try really hard to answer your questions.


## Arduino 
$19.00 USD [Nano 33 BLE](https://store.arduino.cc/usa/nano-33-ble)  (needs USB cable)

$31.50 USD [Nano 33 BLE Sense with headers](https://store.arduino.cc/usa/nano-33-ble-sense-with-headers) The headers actually cover a few of the markings but worth it to get going fast. (needs USB cable)

This product is very new and has some issues as they are trying different programming structures than the Arduino is used to. The enormous open source Adruino community will get this thing working really well soon.  The Sense has a huge number of sensers which will make creating much easier.

Community:  [Arduino BLE Forum](https://forum.arduino.cc/index.php?board=138.0) or the  [Arduino BLE Sense Forum](https://forum.arduino.cc/index.php?board=139.0)
Lots of users here with great suggestions. (Make sure you google questions first or get your hand slapped. Their search auto injects ```site:https://forum.arduino.cc``` into a google search)

## Adafruit 
$25.00 USD [Feather nRF52840](https://www.adafruit.com/product/4062) (needs USB cable)
Has the interesting ability to use CircuitPython, also has a github dedicated to fixing broken bootloaders to get some of these products onto the Arduino platform [Adafruit_DAP](https://github.com/adafruit/Adafruit_DAP)

Community: [Adafruit Forum](https://forums.adafruit.com/index.php)

## MakerDiary
$13.00 USD [nRF52840 MDK USB Dongle (PCBA)](https://store.makerdiary.com/collections/frontpage/products/nrf52840-mdk-usb-dongle)

My First nRF52840 that I really liked, closest to the Nordic product but I am still having a few issues getting this working on lots of examples. This is probably the easiest Dongle to get working with the Nordic SDK.

Community: [Community makerdiary](https://community.makerdiary.com/)


## Particle
$15 USD [Particle.io Xenon](https://store.particle.io/products/xenon). Basically a nRF52840 (USB cable)

$27 USD [Particle Argon](https://store.particle.io/products/Argon) As above but also with Wifi out of the box

$53 USD [Particle Boron LTE North America](https://store.particle.io/collections/boron/products/boron-lte) As above but also with Celluar.

The Particle product is probably the most developed and easiest to use at the moment, however, in my opinion, it has the least open exposure to the SOC abilities. When this product is fully developed it will be very easy to use if you are willing to pay their proposed monthly fees! 

Community: [Particle Community](https://community.particle.io/)

## Fanstel
$18 USD [USB840F, Open Source BLE 5, Thread, Zigbee USB Dongle](https://www.fanstel.com/usb840f/). This USB dongle has no headers, not even sure if it actually has pins, comes in a case, and is fully secured. You need the factory key to work with it. Great for bussiness, bit too much of a pain for my level of hobby/education work.

Community: 


## Sparkfun
$30.00 USD [SparkFun Pro nRF52840 Mini - Bluetooth Development Board](https://www.sparkfun.com/products/15025). (needs USB cable). I do not have one of these but looking at the specs looks like it can act as a usb drive for which you drop programs onto the drive and then the program runs. This might be a very useful method for a school stituation.

Community: [Sparkfun community](https://forum.sparkfun.com/)

# April USB Dongle
$12.00 USD [April USB Dongle 52840](https://blog.aprbrother.com/product/april-usb-dongle-52840). No idea what this is, just found it, seems like only one is left. Kind of cute. The Page says "This USB dongle is very similar with Nordic’s USB dongle PCA10059. But it has less pinouts and button." Comes with a huge antenna.

Community: 


## Any others...





