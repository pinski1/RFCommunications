#include "VirtualWire.h"

const int pinLED = 13;
const int pinRX = 11;

void setup()
{
    delay(1000);
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");
    
    pinMode(pinLED, OUTPUT);

    // Initialise the IO and ISR
    vw_set_rx_pin(pinRX);
    vw_setup(2000);	 // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;

        digitalWrite(pinLED, HIGH); // Flash a light to show received good message
	// Message with a good checksum received, print it.
	Serial.print("Got: ");
	
	for (i = 0; i < buflen; i++)
	{
            Serial.write(buf[i]);
	}
	Serial.println();
        digitalWrite(pinLED, LOW);
    }
}
