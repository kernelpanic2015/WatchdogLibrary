#include <Arduino.h>
#include "Watchdog.h"

// Configure the Watchdog: Timer ID, prescaler, timeout in microseconds
Watchdog wdt(0, 80, 3000000); // Timer ID 0, prescaler 80 (1 us/tick), 3 seconds timeout

void setup()
{
	Serial.begin(115200);
	Serial.println("Initializing...");

	wdt.begin(); // Initialize the watchdog
}

void loop()
{
	// put your main code here, to run repeatedly:
	// Reset the watchdog (feed)
	wdt.reset();

	delay(1000); // Wait for 1 second
}
