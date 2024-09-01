#include <Arduino.h>
#include "Watchdog.h"

/**
 * @brief Global instance of the Watchdog timer.
 *
 * Configures the Watchdog timer with:
 * - Timer ID: 0 (Timer 0)
 * - Prescaler: 80 (1 microsecond per tick)
 * - Timeout: 3000000 microseconds (3 seconds)
 */
Watchdog wdt(0, 80, 3000000); // Timer ID 0, prescaler 80 (1 us/tick), 3 seconds timeout

/**
 * @brief Timestamp of the last crash test execution.
 *
 * Used to keep track of when the last crash test was executed.
 */
unsigned long lastCrashTest = 0;

/**
 * @brief Interval for the crash test in milliseconds.
 *
 * The crash test will be executed every 30 seconds (30000 milliseconds)
 * to verify if the Watchdog is functioning correctly.
 */
const unsigned long crashInterval = 30000;

/**
 * @brief Function to simulate a system crash for testing the Watchdog.
 *
 * This function enters an infinite loop to simulate a system crash.
 * When called, it should cause the Watchdog timer to restart the ESP32 after the timeout period.
 */
void crashTest();

/**
 * @brief Arduino setup function.
 *
 * This function is called once when the ESP32 starts. It initializes the serial communication and
 * configures the Watchdog timer. It is also responsible for setting up any other initializations
 * required for the program.
 */
void setup()
{
	Serial.begin(115200); // Initialize serial communication at 115200 baud rate
	Serial.println("Initializing...");

	wdt.begin(); // Initialize the Watchdog timer
}

/**
 * @brief Arduino loop function.
 *
 * This function is called repeatedly in an infinite loop by the Arduino framework.
 * It resets the Watchdog timer to prevent it from triggering a system reset.
 * Every 30 seconds, it calls crashTest() to simulate a system crash to test if
 * the Watchdog timer is working correctly.
 */
void loop()
{
	// Reset the Watchdog timer to prevent system reset
	wdt.reset();

	// Check if 30 seconds have passed since the last crash test
	// Simulate a system crash to test the Watchdog timer.
	if (millis() - lastCrashTest > crashInterval)
	{
		lastCrashTest = millis(); // Update the timestamp of the last crash test
		Serial.println("Executing crash test...");
		crashTest(); // Call the function to test the Watchdog timer
	}

	delay(1000); // Wait for 1 second before repeating
}

/**
 * @brief Simulate a system crash to test the Watchdog timer.
 *
 * This function intentionally enters an infinite loop, simulating a system crash.
 * When called, the Watchdog timer should detect the lack of activity and reset the ESP32
 * after the specified timeout period (3 seconds).
 */
void crashTest()
{
	Serial.println("Simulating a system crash...");
	while (true)
	{
		// Infinite loop to simulate a crash
		// The Watchdog timer should reset the system after 3 seconds
	}
}
