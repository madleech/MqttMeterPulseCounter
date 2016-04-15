#include "Arduino.h"
#include "config.h"

void setup_led() {
  #ifdef LED
  pinMode(LED, OUTPUT);
  #endif
}

void toggle_led(bool state) {
  #ifdef LED
  digitalWrite(LED, state);
  #endif
}
