#include "config.h"
#include "led.h"
#include "ota.h"
#include "wifi.h"
#include "mqtt.h"
#include "meters.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  
  setup_led();
  setup_wifi();
  setup_mqtt();
  setup_ota();
  setup_meters();
  
  print_wifi_details();
}

void loop() {
  ota_task();
  wifi_task();
  mqtt_task();
}
