# Meter Monitor
Watches for activity on energy meters' LEDs using a CDS photo sensor.

## Topics
Meter readings are published to MQTT topics:

    /meter/1/reading {"count":3,"power":419.60,"kwhr":0.01,"delay":17159,"avg_power":419.21}
    /meter/2/reading {"count":0,"power":0.0,"kwhr":0.0,"delay":0,"avg_power":0}
    /meter/3/reading {"count":0,"power":0.0,"kwhr":0.0,"delay":0,"avg_power":0}
    /meter/uptime 8032

* `uptime` is time in seconds.
* `count` is the number of pulses that have occurred on the meter.
* `power` is the latest calculated power reading in Watts.
* `kwhr` is the current calculated kilowatt-hours, based on the count and pulses per KW.
* `delay` is the most recent delay between pulses on the meter.
* Finaly, `avg_power` is the power reading averaged 6 times over the last 30s.

## Building, uploading
- Enter your wifi and MQTT server details in `config.h`, and adjust pin numbers and pulses per kwhr to suit your meters.
- Optionally, configure your MQTT topics and setup in `mqtt.cpp`
- Build and upload: `platformio run --target upload --environment esp12e`

## Generic notes
Uses OTA programming. Use `avahi-browse _arduino._tcp` to find available arduinos.

The compilation step sets a board type define, so you can choose different defaults based on what board you are targeting. I.e. I develop on a NodeMCU development board, but deploy on a custom ESP12E based board, so the pin numbers are different.

- `BOARD_ESP_12E` -- ESP12E module on custom PCB
- `BOARD_NODE_MCU_V2` -- NodeMCU dev board
