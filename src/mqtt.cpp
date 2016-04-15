#include <PeriodicTask.h>
#include "led.h"
#include "mqtt.h"
#include "wifi.h"
#include "config.h"
#include "meters.h"

PeriodicTask update_meter_average(5000);

void setup_mqtt() {
  mqtt_client.setServer(MQTT_SERVER, 1883);
}

void reconnect_mqtt() {
  // Loop until we're reconnected
  while (!mqtt_client.connected()) {
    toggle_led(HIGH);
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqtt_client.connect(NODE_NAME)) {
      Serial.println("mqtt connected");
      toggle_led(LOW);
      delay(1000);
    } else {
      WiFi.printDiag(Serial);
      Serial.print("mqtt failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqtt_publish_meter_reading(Meter* meter) {
  // if (!meter.has_readings()) return;
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  
  // create JSON
  JsonObject& root = jsonBuffer.createObject();
  root["count"] = meter->count;
  root["power"] = meter->get_power();
  root["kwhr"] = meter->elapsed_kwhr;
  root["delay"] = meter->pulse_length;
  root["avg_power"] = meter->average_power.avg();
  
  // write JSON to buffer
  char buffer[256];
  root.printTo(buffer, sizeof(buffer));
  
  // publish
  char topic[20];
  snprintf(topic, 20, "meter/%d/reading", meter->id);
  mqtt_client.publish(topic, buffer);
}

void mqtt_publish_uptime() {
  static char buffer[10];
  snprintf(buffer, 10, "%lu", millis() / 1000);
  mqtt_client.publish("meter/uptime", buffer);
}

void mqtt_task() {
  // check connection
  if (wifi_connected()) {
    if (!mqtt_client.connected()) reconnect_mqtt();
    mqtt_client.loop();
  
    // update mqtt
    if (update_mqtt.tick()) {
      toggle_led(HIGH);
      
      mqtt_publish_meter_reading(&meter1);
      mqtt_publish_meter_reading(&meter2);
      mqtt_publish_meter_reading(&meter3);
      mqtt_publish_uptime();
      
      toggle_led(LOW);
    }
  }
  
  if (update_meter_average.tick()) {
    meter1.update_average();
    meter2.update_average();
    meter3.update_average();
  }
}
