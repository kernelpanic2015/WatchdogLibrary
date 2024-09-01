// Watchdog.cpp
#include "Watchdog.h"

// Construtor da classe Watchdog
Watchdog::Watchdog(uint8_t timerId, uint16_t prescaler, uint32_t timeout_us)
    : timerId(timerId), prescaler(prescaler), timeout(timeout_us), timer(NULL) {}

// Inicializa o temporizador
void Watchdog::begin()
{
    timer = timerBegin(timerId, prescaler, true);            // Cria o temporizador
    timerAttachInterrupt(timer, &Watchdog::onTimeout, true); // Anexa o callback
    timerAlarmWrite(timer, timeout, true);                   // Configura o tempo de alarme (timeout)
    timerAlarmEnable(timer);                                 // Habilita o alarme
}

// Reseta o temporizador (alimenta o watchdog)
void Watchdog::reset()
{
    timerWrite(timer, 0); // Reseta o contador do temporizador
}

// Função de callback chamada quando o temporizador atinge o timeout
void IRAM_ATTR Watchdog::onTimeout()
{
    ets_printf("(watchdog) reiniciar\n");
    esp_restart(); // Reinicia o ESP32
}
