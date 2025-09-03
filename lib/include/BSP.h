#ifndef BSP_H
#define BSP_H

#ifdef ARDUINO_ARCH_AVR
  // Para Arduino Uno/Mega
  #include <Arduino_FreeRTOS.h>
#endif

#ifdef ARDUINO_ARCH_ESP32
  // Para ESP32
        #include "freertos/FreeRTOS.h"
        #include "freertos/task.h"
        #include "freertos/queue.h"
       // #include <HardwareSerial.h>
       // #include "wiring_private.h"
#endif

#include <HardwareSerial.h>
#include "wiring_private.h"

// --- imprimir.c ---
void imprimirMensaje(const char *msg);
void imprimirValor(const char *etiqueta, int valor);

// --- gpio.c ---
void gpioInitPin(uint8_t pin, uint8_t mode);   // Inicializa pines como IN/OUT
void gpioSet(uint8_t pin, bool estado); // Cambia estado de un pin

// --- adc.c ---
int leerADC(uint8_t pin);

// Inicialización global
void bspInit();

bool gpioRead(uint8_t pin);

// Pines
#define LED_PIN   13
#define BTN_PIN   12
#define ADC_PIN   A0


#endif
