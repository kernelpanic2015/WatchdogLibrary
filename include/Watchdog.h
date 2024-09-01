// Watchdog.h
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <Arduino.h>

class Watchdog
{
public:
    Watchdog(uint8_t timerId, uint16_t prescaler, uint32_t timeout_us);

    // Inicializa o temporizador
    void begin();

    // Reseta o temporizador (alimenta o watchdog)
    void reset();

private:
    hw_timer_t *timer;  // Ponteiro para o temporizador de hardware
    uint8_t timerId;    // ID do temporizador
    uint16_t prescaler; // Prescaler para ajustar a frequência do temporizador
    uint32_t timeout;   // Tempo de timeout em microsegundos

    // Função estática de callback que será chamada pelo temporizador
    static void IRAM_ATTR onTimeout();
};

#endif
