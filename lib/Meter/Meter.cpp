#include "Meter.h"
#include "Arduino.h"

Meter::Meter(uint8_t id, unsigned int pulses_per_kwhr)
: id(id)
, _pulses_per_kwhr(pulses_per_kwhr)
, count(0)
, power(0)
, elapsed_kwhr(0)
, average_power(5)
{
}

// interrupt callback
void Meter::pulse()
{
  // debounce input, ignore triggers less than 1/2s = 500ms = 500,000µs
  if ((millis() - _last_pulse_time) < 500) return;
  
  // used to measure time between pulses.
  _pulse_time = millis();
  
  // increment pulse count
  count++;
  
  // calculate pulse length
  pulse_length = _pulse_time - _last_pulse_time;
  
  // calculate power based on pulse length
  power = (1000.0 / _pulses_per_kwhr) * 3600.0 / pulse_length * 1000.0;
  
  // find kwh elapsed (kWhr)
  elapsed_kwhr = (1.0 * count / (_pulses_per_kwhr));
  
  // remember pulse time for next time
  _last_pulse_time = _pulse_time;
}

bool Meter::has_readings() const
{
  return count > 0;
}

double Meter::get_power()
{
  unsigned long current_pulse_length = millis() - _last_pulse_time;
  
  // if current pulse is shorter than previous whole pulse, then we haven't had a pulse yet
  // so use previous whole pulse length instead.
  if (current_pulse_length < pulse_length) current_pulse_length = pulse_length;
  
  // calculate power based on pulse length
  return pulse_length == 0
    ? 0
    : (1000.0 / _pulses_per_kwhr) * 3600.0 / pulse_length * 1000.0;
}

void Meter::update_average()
{
  // update running average
  average_power.add(get_power());
}
