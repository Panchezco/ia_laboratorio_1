#include "BSP.h"


#ifdef ARDUINO_ARCH_AVR
  #include <Arduino.h>
#endif

#ifdef ARDUINO_ARCH_ESP32
  #include "driver/adc.h"
  #include "esp_adc_cal.h"
#endif

int leerADC(uint8_t pin) {
    
#ifdef ARDUINO_ARCH_AVR
    // Usa la función de Arduino
    return analogRead(pin);
#endif

#ifdef ARDUINO_ARCH_ESP32
    // Aquí mapeamos el pin al canal ADC correspondiente
    adc1_channel_t canal;

    switch(pin){
        case 32: canal = ADC1_CHANNEL_4; break;
        case 33: canal = ADC1_CHANNEL_5; break;
        case 34: canal = ADC1_CHANNEL_6; break;
        case 35: canal = ADC1_CHANNEL_7; break;
        case 36: canal = ADC1_CHANNEL_0; break;
        case 39: canal = ADC1_CHANNEL_3; break;
        default: return -1; // Pin no soportado
    }

    // Configuramos el ADC una sola vez
    static bool adc_configurado = false;
    if(!adc_configurado){
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(canal, ADC_ATTEN_DB_11);
        adc_configurado = true;
    }

    return adc1_get_raw(canal);  // Devuelve valor 0-4095
#endif
}

