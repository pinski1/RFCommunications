#Radio Communications Tester
Tests a one-way communications link between Arduino's.

##Ingredients
The parts used for testing are:
* XD-FST - 433MHz Transmitter
* XD-RF-5V - 433MHz Receiver
* Arduino x2
* Jumper wires

##Architecture
Communication systems are typically modeled on the OSI model, an abstracted 7 layer model where each layer uses the ones below it to send messages and passes messages to the ones above it.

###OSI Model Layers
7. Application layer - High-level APIs, including resource sharing, remote file access, directory services and virtual terminals.
6. Presentation layer - Translation of data between a networking service and an application; including character encoding, data compression and encryption/decryption.
5. Session layer - Managing communication sessions, i.e. continuous exchange of information in the form of multiple back-and-forth transmissions between two nodes.
4. Transport layer - Reliable transmission of data segments between points on a network, including segmentation, acknowledgement and multiplexing
3. Network layer - Structuring and managing a multi-node network, including addressing, routing and traffic control.
2. Data Link layer - Reliable transmission of data frames between two nodes connected by a physical layer.
1. Physical layer - Transmission and reception of raw bit streams over a physical medium.
Taken from [Wikipedia - OSI model](http://en.wikipedia.org/wiki/OSI_model).

###XD-RF Considerations
This is to be used as a simple telemetry system for a theoretical (sub-)orbital rocket. The main limitation of this system is the unidirectional data transfer, rocket to ground station. This is advantageous as we do not want the telemetry system to get hung up trying to re-transmit un-acknowledged messages.

We will want to send simple mesages regularly with the following data:
* IMU values - 10 ?bit integers
* Valve status - 8 boolean values
* GPS readings - Lat, Lon, Alt ???
* Flow sensors - ???
* Fuel remaining - ???

The basic message format would be:
* 4 bytes - Header - Identifies the start of a message
* 4 bytes - Sequence number - Tracks the position of the message
* 2 bytes - Length - The number of message data bytes
* 2 bytes - Type/Name - A name to attach to the data
* n bytes - Data - Message data
* 2 bytes - CRC - Allows confirmation of message validity
* 2 bytes - Footer - Identifies the end of a message


##Code
Tested on Arduino Uno & Mega 2560 with IDE 1.0.5.

###XD_RF_5V
This is a very simple library that was written by [Summerfuel Robotics](https://sites.google.com/site/summerfuelrobots/arduino-sensor-tutorials/rf-wireless-transmitter-receiver-module-433mhz-for-arduino) to enable control of RF power sockets. As such the library sends messages using the RF power socet protocol which allows for verification that the RF link is working but not ideal for our needs.

###VirtualWire
[VirtualWire](https://www.pjrc.com/teensy/td_libs_VirtualWire.html) was written to allow simple but effective use of these very cheap but basic RF modules. For our purposes it is ideal as it automatically adds training symbols, header, footer, length and checksum. This means we will only need to add a sequence number, name/type and the data to be sent.

#Licences
The implimentation code is available as part of the Public Domain.

##XD_RF
Is available under a GPL v2.1 licence.

##VirtualWire
Is available under a GPL v2 licence or Comercial licence. It is used here under GPL v2 licence.
