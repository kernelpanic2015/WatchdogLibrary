# WatchdogLibrary

A simple Watchdog Timer library for the ESP32, designed to make it easy to use and integrate a watchdog timer in your projects. This library helps monitor the proper execution of your code and automatically restarts the ESP32 in case of a software failure.
A simple Watchdog Timer library for ESP32.

## Installation

To include this library in your PlatformIO project, add the following line to your `platformio.ini`:

```ini
lib_deps =
    https://github.com/kernelpanic2015/WatchdogLibrary
```

## Usage
Include the library in your project and initialize it in your code as shown below:

```cpp
#include <Arduino.h>
#include "Watchdog.h"

// Configure the Watchdog: Timer ID, prescaler, timeout in microseconds
Watchdog wdt(0, 80, 3000000); // Timer ID 0, prescaler 80 (1 us/tick), 3 seconds timeout

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");

    wdt.begin(); // Initialize the watchdog
}

void loop() {
    // Simulate main code
    Serial.println("Running main loop...");

    // Reset the watchdog (feed)
    wdt.reset();

    delay(1000); // Wait for 1 second
}

```
### Explanation

* **Watchdog Timer Initialization**: Watchdog wdt(0, 80, 3000000); initializes a watchdog timer on Timer 0 with a prescaler of 80 (1 microsecond per tick) and a timeout period of 3 seconds (3000000 microseconds).

* **Feeding the Watchdog**: wdt.reset(); must be called periodically in the loop() function to reset the timer and prevent it from expiring. If the timer expires, it will automatically restart the ESP32.

## Crash Test Example

To ensure that the Watchdog Timer is functioning correctly, you can perform a crash test by deliberately simulating a system crash. This can be done by creating a situation where the Watchdog is not reset, causing it to trigger a system restart.

An example of such a test can be found in the example directory of this repository:

[WatchdogExample](./example/WatchdogExample)

In this example, a crash test is executed every 30 seconds to verify that the Watchdog resets the ESP32 as expected.


## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request if you have suggestions or improvements.

## License

This library is open-source and available under the [MIT License](./LICENSE).
