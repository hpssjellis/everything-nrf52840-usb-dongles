# Everything About the nRF52840 USB
Anything I can find about the various nrf52840 usb dongles (With USB cables or the Dongles) by Nordic, Arduino, Adafruit, Sparkfun, MakerDiary and others


Created Dec 7th, 2019

# Basic concept

The Nordic nRF52840 SOC is getting a lot of publicity for it's great BLE abilities and has been embedded in many boards from Nordic, Particle, Adafruit, Sparkfun, MakerDiary and Arduino. Unfortunately each company has their own way to program these boards with varying exposure to the SOC's abilities.

# Important links

For pinout comparison chart    [pinout-comparison-chart.md](pinout-comparison-chart.md)


My Openthread and Nordic SDK Online Browser compatible Docker. (Yes it is amazing).  [My Gitpod Github Openthread](https://github.com/hpssjellis/my-gitpod-of-openthread) This takes a very long time to build from scratch. First try the snapshot, takes a while to load, but worth it, Generated Dec 4th, 2019 updated with the Nordic sdk.


[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io#snapshot/e709c382-8574-4775-876c-002bfeecc374)



For random links used while making this    [random-links.md](random-links.md)



.



.



# The different Boards

## Nordic 
$10.00 USD [nRF52840 USB Dongle](https://www.digikey.com/product-detail/en/nordic-semiconductor-asa/NRF52840-DONGLE/1490-1073-ND/9491124?_ga=2.112542724.1204958722.1575703702-701218832.1573252054&_gac=1.12604485.1574457358.Cj0KCQiAq97uBRCwARIsADTziyako1nHRHIJGlUf6ZprMFUFuqiaruXRiJ3sGP4mQ3FC3kIQmQxaQZsaAswzEALw_wcB)

The best, but most confusing set of examples are at the [Nordic NRF5 SDK](https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK/Download). 


## Arduino 
$19.00 USD [Nano 33 BLE](https://store.arduino.cc/usa/nano-33-ble)  
$31.50 USD [Nano 33 BLE Sense with headers](https://store.arduino.cc/usa/nano-33-ble-sense-with-headers) The headers actually cover a few of the markings but worth it to get going fast.

This product is very new and has some issues as they are trying different programming structures than the Arduino is used to. The enormous open source Adruino community will get this thing working really well soon.  The Sense has a huge number of sensers which will make creating much easier.



## Adafruit 
$25.00 USD [Feather nRF52840]
Has the interesting ability to use CircuitPython, also has a github dedicated to fixing broken bootloaders to get some of these products onto the Arduino platform [Adafruit_DAP](https://github.com/adafruit/Adafruit_DAP)

## MakerDiary
$13.00 USD [nRF52840 MDK USB Dongle (PCBA)](https://store.makerdiary.com/collections/frontpage/products/nrf52840-mdk-usb-dongle)

My First nRF52840 that I really liked, closest to the Nordic product but I am still having a few issues getting this working on lots of examples. This is probably the easiest Dongle to get working with the Nordic SDK.


## Particle
$15 USD [Particle.io Xenon](https://store.particle.io/products/xenon). Basically a nRF52840 USB Dongle (Needs cable, not a dongle)
$27 USD [Particle Argon](https://store.particle.io/products/Argon) As above but with Wifi out of the box
$53 USD [Particle Boron LTE North America](https://store.particle.io/products/Argon) As above but with Wifi and Celluar out of the box

The Particle product is probably the most developed and easiest to use at the moment, however, in my opinion, it has the least open exposure to the SOC abilities. When this product is fully developed it will be very easy to use if you are willing to pay their proposeed monthly fees.  



## Sparkfun
$30.00 USD [SparkFun Pro nRF52840 Mini - Bluetooth Development Board](https://www.sparkfun.com/products/15025). Also need a usb cable, not a dongle.







