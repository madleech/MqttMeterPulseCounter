#include <Meter.h>
#include "meters.h"
#include "config.h"

Meter meter1(1, METER_1_PULSES_PER_KWHR);
Meter meter2(2, METER_2_PULSES_PER_KWHR);
Meter meter3(3, METER_3_PULSES_PER_KWHR);

void meter1_pulse() { meter1.pulse(); }
void meter2_pulse() { meter2.pulse(); }
void meter3_pulse() { meter3.pulse(); }

void setup_meters() {
  pinMode(METER_1_PIN, INPUT);
  pinMode(METER_2_PIN, INPUT);
  pinMode(METER_3_PIN, INPUT);
  
  attachInterrupt(METER_1_PIN, meter1_pulse, RISING);
  attachInterrupt(METER_2_PIN, meter2_pulse, RISING);
  attachInterrupt(METER_3_PIN, meter3_pulse, RISING);
}
