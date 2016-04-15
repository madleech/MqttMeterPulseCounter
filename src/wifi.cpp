#include "led.h"
#include "wifi.h"
#include "config.h"

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
}

void print_wifi_details() {
  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());
}

bool wifi_connected() {
  return WiFi.status() == WL_CONNECTED;
}

void reconnect_wifi() {
  while (!wifi_connected()) {
    toggle_led(HIGH);
    Serial.print("Attempting Wifi connection...");
    setup_wifi();
    toggle_led(LOW);
  }
}

void wifi_task() {
  if (!wifi_connected()) reconnect_wifi();
}
