#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <PeriodicTask.h>
#include <Meter.h>
#include "wifi.h"

#ifndef MQTT_H
#define MQTT_H

const int JSON_BUFFER_SIZE = JSON_OBJECT_SIZE(5);

static PeriodicTask update_mqtt(30000);
static PubSubClient mqtt_client(espClient);

void setup_mqtt();
void reconnect_mqtt();
void mqtt_task();

#endif
