#ifndef SINE_GENERATOR_H
#define SINE_GENERATOR_H

#include "Arduino.h"
#include "Waveform_generator.h"


// Class that represents a sine wave. The wave starts at X=0 with no values and advances
// one step along the X axis with each call of next_value. Only the most recently 
// calculated value is stored within the class.
class Sine_generator : public Oscillating_generator
{
public:
  Sine_generator( byte min_in, byte max_in, float frequency, float phase = 0 );

  // The wave's lower bound on the Y axis [0,255]
  float minimum() const { return minimum_*MAX_LEVEL; }
  
  // The wave's upper bound on the Y axis [0,255]
  float maximum() const { return maximum_*MAX_LEVEL; }
  
  // Frequency multiplier. This is a factor, not a time unit (since the wave's 
  // actual frequency in milliseconds depends on how often next_value is called).
  const float& frequency() const { return frequency_; }
  
  // Phase of the wave in radians. The waveform is shifted along the x axis 
  // by this amount. 0 is a sine wave, pi/2 is a cosine. 
  const float& phase() const { return phase_; }
  
  void set( float new_frequency, float new_phase, float new_minimum, float new_maximum );
  void set_frequency( float new_frequency ) { frequency_ = new_frequency; }
  void set_phase( float new_phase ) { phase_ = new_phase; }

  // from Waveform_generator
  byte next_value();
  float next_raw_value();
  
  // Prints the wave values to the serial console. Call Serial.begin before using.
  void test();

private:  
  void update_values();
  
  // All in the range [0,1]
  float frequency_;
  float phase_;
};




// NOT DONE (obviously)
class Linear_generator : public Oscillating_generator
{
public:
  enum Wave_type { SAWTOOTH, TRIANGLE }; // could make separate classes if more time
  
  Linear_generator( Wave_type type, byte minimum, byte maximum, byte start_value = 0 );
  
  // from Waveform_generator
  byte value() const { return raw_value_*MAX_LEVEL; }
  byte next_value();
  float raw_value() const { return raw_value_; }
  float next_raw_value();
  
  // prints values to serial console. be sure to call Serial.begin before
  void test();
  
private:
  void update_value();
  signed char direction_; //only for triangle waves - 1=up, -1=down
  Wave_type type_;
  float raw_value_;
  float step_size_;
};


#endif