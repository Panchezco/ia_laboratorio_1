#include "BSP.h"



#ifdef ARDUINO_ARCH_AVR
  #include <Arduino.h>
#endif

#ifdef ARDUINO_ARCH_ESP32
  #include "driver/gpio.h"
#endif

// Inicializa los GPIO necesarios

void gpioInitPin(uint8_t pin, uint8_t mode) {
#ifdef ARDUINO_ARCH_AVR
    pinMode(pin, mode);   // Arduino ya entiende INPUT, OUTPUT, INPUT_PULLUP
#endif

#ifdef ARDUINO_ARCH_ESP32
    gpio_reset_pin((gpio_num_t)pin);

    if (mode == INPUT) {
        gpio_set_direction((gpio_num_t)pin, GPIO_MODE_INPUT);
    } else if (mode == OUTPUT) {
        gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT);
    } else if (mode == INPUT_PULLUP) {
        gpio_set_direction((gpio_num_t)pin, GPIO_MODE_INPUT);
        gpio_pulldown_dis((gpio_num_t)pin);
        gpio_pullup_en((gpio_num_t)pin);
    }
#endif
}

// Controla un GPIO: si está apagado, lo enciende; si está encendido, lo apaga
void gpioControl(uint8_t pin) {
#ifdef ARDUINO_ARCH_AVR
    digitalWrite(pin, !digitalRead(pin));  // Cambia el estado
#endif

#ifdef ARDUINO_ARCH_ESP32
    int nivel = gpio_get_level((gpio_num_t)pin); // Lee nivel actual
    gpio_set_level((gpio_num_t)pin, !nivel);    // Cambia el estado
#endif
}

// Establece un GPIO en alto o bajo explícitamente
void gpioSet(uint8_t pin, bool estado) {
#ifdef ARDUINO_ARCH_AVR
    digitalWrite(pin, estado ? HIGH : LOW);
#endif

#ifdef ARDUINO_ARCH_ESP32
    gpio_set_level((gpio_num_t)pin, estado ? 1 : 0);
#endif
}

bool gpioRead(uint8_t pin) {
#ifdef ARDUINO_ARCH_AVR
    return digitalRead(pin);
#endif

#ifdef ARDUINO_ARCH_ESP32
    return gpio_get_level((gpio_num_t)pin);
#endif
}



// Inicializa una interrupción

void gpioAttachInterrupt(uint8_t pin, void (*isr)(), int mode) {
#ifdef ARDUINO_ARCH_AVR
    // En Arduino clásico
    attachInterrupt(digitalPinToInterrupt(pin), isr, mode);
#endif

#ifdef ARDUINO_ARCH_ESP32
    // En ESP32
    gpio_reset_pin((gpio_num_t)pin);
    gpio_set_direction((gpio_num_t)pin, GPIO_MODE_INPUT);

    // Configuración básica
    gpio_set_intr_type((gpio_num_t)pin, 
        mode == RISING    ? GPIO_INTR_POSEDGE :
        mode == FALLING   ? GPIO_INTR_NEGEDGE :
        mode == CHANGE    ? GPIO_INTR_ANYEDGE :
                            GPIO_INTR_DISABLE);

    // Registrar el handler
    gpio_isr_handler_add((gpio_num_t)pin, (gpio_isr_t)isr, NULL);
#endif
}

// Deshabilita la interrupcinb

void gpioDetachInterrupt(uint8_t pin) {
#ifdef ARDUINO_ARCH_AVR
    detachInterrupt(digitalPinToInterrupt(pin));
#endif

#ifdef ARDUINO_ARCH_ESP32
    gpio_isr_handler_remove((gpio_num_t)pin);
#endif
}


// Habilita el servicio global de ISR (ESP32 necesita init)

void gpioInitInterrupts() {
#ifdef ARDUINO_ARCH_ESP32
    static bool initialized = false;
    if (!initialized) {
        gpio_install_isr_service(0);  // instala el servicio ISR
        initialized = true;
    }
#endif
}