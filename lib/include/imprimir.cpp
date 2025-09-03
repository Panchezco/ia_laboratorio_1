#include "BSP.h"

#ifdef ARDUINO_ARCH_AVR
  #include <Arduino.h>
#endif

#ifdef ARDUINO_ARCH_ESP32
  #include "esp_system.h"
  #include "esp_log.h"
#endif

void imprimirMensaje(const char *msg) {
#ifdef ARDUINO_ARCH_AVR
    Serial.begin(9600);
    Serial.print("Mensaje: ");
    Serial.println(msg);
#endif

#ifdef ARDUINO_ARCH_ESP32
    // En ESP32 usamos ESP-IDF logging
    printf("Mensaje: %s\n", msg);
#endif
}

void imprimirValor(const char *etiqueta, int valor) {
#ifdef ARDUINO_ARCH_AVR
    Serial.begin(9600);
    Serial.print(etiqueta);
    Serial.print(": ");
    Serial.println(valor);
#endif

#ifdef ARDUINO_ARCH_ESP32
     Serial.begin(9600);
    printf("%s: %d\n", etiqueta, valor);
#endif
}