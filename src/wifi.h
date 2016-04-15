#include <ESP8266WiFi.h>

#ifndef WIFI_H
#define WIFI_H

static WiFiClient espClient;

void setup_wifi();
void print_wifi_details();
void reconnect_wifi();
bool wifi_connected();
void wifi_task();

#endif
