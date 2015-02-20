#include "VirtualWire.h"

const int pinLED = 13;
const int pinTX = 12;

void setup()
{
  // Initialise the IO and ISR
  vw_set_tx_pin(pinTX);
  vw_setup(2000);	 // Bits per sec
}

byte count = 1;

void loop()
{
  char msg[7] = {'h','e','l','l','o',' ','#'};

  msg[6] = count;
  digitalWrite(pinLED, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(pinLED, LOW);
  delay(1000);
  count = count + 1;
}
