// Watchdog.cpp
#include "Watchdog.h"

/**
 * @brief Constructor for the Watchdog class.
 *
 * Initializes the Watchdog timer with the specified parameters:
 * - Timer ID: Unique identifier for the timer.
 * - Prescaler: Value to divide the timer clock.
 * - Timeout: Timeout period in microseconds after which the Watchdog will trigger.
 *
 * @param timerId The ID of the timer to be used.
 * @param prescaler The prescaler value to set the timer frequency.
 * @param timeout_us The timeout duration in microseconds.
 */
Watchdog::Watchdog(uint8_t timerId, uint16_t prescaler, uint32_t timeout_us)
    : timerId(timerId), prescaler(prescaler), timeout(timeout_us), timer(NULL) {}

/**
 * @brief Initializes the Watchdog timer.
 *
 * This function sets up the timer with the specified ID and prescaler. It attaches
 * the interrupt callback function that will be called when the timer expires,
 * configures the timer alarm with the specified timeout, and enables the timer alarm.
 */
void Watchdog::begin()
{
    timer = timerBegin(timerId, prescaler, true);            // Create the timer
    timerAttachInterrupt(timer, &Watchdog::onTimeout, true); // Attach the callback function
    timerAlarmWrite(timer, timeout, true);                   // Set the alarm timeout
    timerAlarmEnable(timer);                                 // Enable the alarm
}

/**
 * @brief Resets the Watchdog timer.
 *
 * This function resets the timer to prevent it from expiring. It is used to "feed"
 * the Watchdog and prevent it from triggering a system restart.
 */
void Watchdog::reset()
{
    timerWrite(timer, 0); // Reset the timer counter
}

/**
 * @brief Callback function called when the timer timeout occurs.
 *
 * This function is invoked when the Watchdog timer expires. It logs a message to the
 * console and restarts the ESP32 to recover from a potential system failure.
 *
 * This function must be marked with `IRAM_ATTR` to ensure it is executed from RAM
 * and not from flash memory, which is important for interrupt service routines.
 */
void IRAM_ATTR Watchdog::onTimeout()
{
    ets_printf("(watchdog) restarting\n");
    esp_restart(); // Restart the ESP32
}
