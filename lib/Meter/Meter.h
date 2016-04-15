#include "Arduino.h"
#include <RunningAverage.h>

#ifndef METER_H
#define METER_H

class Meter
{
	public:
		Meter(uint8_t id, unsigned int pulses_per_kwhr);
		
		void pulse();
		bool has_readings() const;
		double get_power();
		void update_average();
		
		uint8_t id;
		volatile unsigned long pulse_length;
		volatile unsigned long count;
		volatile unsigned long power;
		volatile double elapsed_kwhr;
		
		RunningAverage average_power;
  
  private:
		volatile unsigned int _pulses_per_kwhr;
    volatile unsigned long _pulse_time;
		volatile unsigned long _last_pulse_time;
};

#endif
