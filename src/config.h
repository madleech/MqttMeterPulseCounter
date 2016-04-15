// config

#define WIFI_SSID "..."
#define WIFI_PASSWORD "..."
#define MQTT_SERVER "..."
#define NODE_NAME "meter-monitor"

#define METER_1_PULSES_PER_KWHR 500
#define METER_2_PULSES_PER_KWHR 500
#define METER_3_PULSES_PER_KWHR 1000

#ifdef BOARD_ESP_12E
  #define LED 16
  #define METER_1_PIN 2
  #define METER_2_PIN 5
  #define METER_3_PIN 4
#else
  #define METER_1_PIN D5
  #define METER_2_PIN D6
  #define METER_3_PIN D7
#endif
