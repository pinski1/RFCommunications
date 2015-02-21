#include "VirtualWire.h"

const int pinLED = 13;
const int pinTX = 12;

unsigned char sequenceNum = 0x00;
String messageTypes[9] = {"ACCL", "GYRO", "MAGN", "BARO", "LATI", "LONG", "ALTI", "VSTA", "LSTA"};

void setup()
{
  // Initialise the IO and ISR
  pinMode(pinLED, OUTPUT);

  vw_set_tx_pin(pinTX);
  vw_setup(2000);	 // Bits per sec
}

byte count = 1;

void loop()
{
  String message;
  char buffer[25];

  message = String(sequenceNum, DEC) + ' ' + messageTypes[sequenceNum%9] + ':' + "8888";
  message.toCharArray(buffer, 25);

  digitalWrite(pinLED, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)buffer, message.length());
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(pinLED, LOW);

  sequenceNum ++;
  
  delay(1000);
}


