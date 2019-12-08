# Everything About the nRF52840 USB Dongles
Anything I can find about the various nrf52840 usb  (With USB cables or direct plugin dongles) by Nordic, Arduino, Adafruit, Sparkfun, MakerDiary and others


Created Dec 7th, 2019


  
# Big Picture
I want to make the best High School North American Robotics Program. 
1. I have already finished and student tested for 3 years a wifi based Robotics program Github at: [particle.io-photon-high-school-robotics](https://github.com/hpssjellis/particle.io-photon-high-school-robotics)  With Sensors, Actuators, web control, SPI, I2C, uArt and websockets. 
1. [A Machine Learning Javascript Tensorflow.js Program](https://www.rocksetta.com/tensorflowjs/). 
3. A cryptocurrency Internet of Things Program using IOTA. The hackster [here](https://www.hackster.io/jeremy-ellis/particle-photon-pay-iota-to-read-sensors-edb7b8). 
4.Now I need to update my High School course to include [BLE](https://en.wikipedia.org/wiki/Bluetooth_Low_Energy) and [Openthread](http://openthread.io)  




# Basic Concept

The [Nordic nRF52840 SOC](https://www.nordicsemi.com/Products/Low-power-short-range-wireless/nRF52840) is getting a lot of publicity for it's great BLE (Bluetooth Low Energy) abilities and has been embedded in many boards from Nordic, Particle, Adafruit, Sparkfun, MakerDiary and Arduino. 


# The Problem

All the above companies that use the nRF52840 SOC embedded boards have their own technique for programming the boards, making it very difficult to pick and choose the product combination that works well in the classroom. Luckily Arduino has entered the race with their new Nano 33 BLE. That brings a huge community of capable hobbyists and professional engineers to the issue.  





  
# My (our) Solution

I would like to see how many of these boards we can get working on both the Nordic and Arduino platforms. Then I can choose which boards to include in my new version of my High School Robotics Course. 



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
$30.00 USD [SparkFun Pro nRF52840 Mini - Bluetooth Development Board](https://www.sparkfun.com/products/15025). (needs USB cable). I do not have one of these but looking at the specs looks like it might have wifi as well as bluetooth, which might be interesting to try.

Community: [Sparkfun community](https://forum.sparkfun.com/)

# April USB Dongle
$12.00 USD [April USB Dongle 52840](https://blog.aprbrother.com/product/april-usb-dongle-52840). No idea what this is, just found it, seems like only one is left. Kind of cute. The Page says "This USB dongle is very similar with Nordic’s USB dongle PCA10059. But it has less pinouts and button." Comes with a huge antenna.

Community: 


## Any others...





