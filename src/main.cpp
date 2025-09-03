#include <BSP.h>

// Pines
#define LED_PIN      2
#define BTN_PIN      15
#define HUM_PIN      A0
#define LDR_PIN      A3
#define TEMP_PIN     A4


// Modos de operación
typedef enum {
  MODE_OFF,
  MODE_LOW_POWER,
  MODE_RUN
} system_mode_t;

system_mode_t currentMode = MODE_OFF;

// Variables para LED parpadeo
unsigned long lastBlinkTime = 0;
bool ledState = false;

// Variables para ADC
unsigned long lastADCReadTime = 0;
const unsigned long adcInterval = 1000; // 1 s

void setup() {
  Serial.begin(9600);

  gpioInitPin(LED_PIN, OUTPUT);
  gpioInitPin(BTN_PIN, INPUT_PULLUP);

  imprimirMensaje("Sistema inicializado -> MODO OFF");
}

void loop() {
  unsigned long currentMillis = millis();

  // ------------------- Forzar RUN con pin a GND -------------------
  if (gpioRead(BTN_PIN) == LOW) {
    currentMode = MODE_RUN;
  } else if (currentMode != MODE_OFF) {
    currentMode = MODE_LOW_POWER; // si quitas el cable, vuelve a LOW_POWER
  }

  // ------------------- LED indicador de estado -------------------
  switch (currentMode) {
    case MODE_OFF:
      gpioSet(LED_PIN, false);
      break;

    case MODE_LOW_POWER:
      if (currentMillis - lastBlinkTime >= (ledState ? 900 : 100)) {
        ledState = !ledState;
        gpioSet(LED_PIN, ledState);
        lastBlinkTime = currentMillis;
      }
      break;

    case MODE_RUN:
      if (currentMillis - lastBlinkTime >= 200) {
        ledState = !ledState;
        gpioSet(LED_PIN, ledState);
        lastBlinkTime = currentMillis;
      }
      break;
  }

  // ------------------- Lectura de sensores -------------------
  if (currentMillis - lastADCReadTime >= adcInterval) {
    lastADCReadTime = currentMillis;

    if (currentMode == MODE_RUN) {
      int humValue  = leerADC(HUM_PIN);
      int ldrValue  = leerADC(LDR_PIN);
      int tempValue = leerADC(TEMP_PIN);

      imprimirValor("Humedad", humValue);
      imprimirValor("Fotorresistencia", ldrValue);
      imprimirValor("Temperatura", tempValue);
    } else {
      imprimirMensaje("No_Disponible");
    }
  }
}