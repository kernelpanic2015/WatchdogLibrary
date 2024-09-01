// Watchdog.h
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <Arduino.h>

/**
 * @brief Class for managing a Watchdog Timer.
 *
 * This class provides an interface for configuring and using a hardware watchdog timer
 * on the ESP32. The Watchdog Timer helps monitor the proper execution of code and
 * can trigger a system restart if the code fails to reset the timer within the
 * specified timeout period.
 */
class Watchdog
{
public:
    /**
     * @brief Constructor for the Watchdog class.
     *
     * Initializes the Watchdog timer with the given parameters.
     *
     * @param timerId The ID of the timer to be used (e.g., 0, 1, 2, 3).
     * @param prescaler The prescaler value to adjust the timer frequency.
     * @param timeout_us The timeout period in microseconds after which the Watchdog triggers.
     */
    Watchdog(uint8_t timerId, uint16_t prescaler, uint32_t timeout_us);

    /**
     * @brief Initializes the Watchdog timer.
     *
     * Sets up the hardware timer, attaches the interrupt service routine (ISR) for
     * handling timeout events, configures the alarm with the specified timeout,
     * and enables the timer alarm.
     */
    void begin();

    /**
     * @brief Resets the Watchdog timer.
     *
     * Feeds the Watchdog timer to prevent it from expiring. This method should be called
     * periodically within the main loop to ensure the Watchdog timer does not trigger
     * a system restart.
     */
    void reset();

private:
    hw_timer_t *timer;  ///< Pointer to the hardware timer instance.
    uint8_t timerId;    ///< ID of the timer.
    uint16_t prescaler; ///< Prescaler value for adjusting the timer frequency.
    uint32_t timeout;   ///< Timeout duration in microseconds.

    /**
     * @brief Static callback function called on timer timeout.
     *
     * This static function is called when the Watchdog timer expires. It logs a message
     * and initiates a system restart. It must be marked with `IRAM_ATTR` to ensure it
     * is executed from RAM, which is required for interrupt service routines.
     */
    static void IRAM_ATTR onTimeout();
};

#endif
