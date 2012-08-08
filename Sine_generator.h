#include "Arduino.h"
#define PI 3.14159


// Class that represents a sine wave. The wave starts at X=0 with no values and advances
// one step along the X axis with each call of next_value. Only the most recently 
// calculated value is stored within the class.
class Sine_generator
{
public:
  Sine_generator( byte min_in, byte max_in, float frequency, float phase );

  // The wave's lower bound on the Y axis
  byte minimum() const { return minimum_; }
  
  // The wave's upper bound on the Y axis
  byte maximum() const { return maximum_; }
  
  // Frequency multiplier. This is a factor, not a time unit (since the wave's 
  // actual frequency in milliseconds depends on how often next_value is called).
  const float& frequency() const { return frequency_; }
  
  // Phase of the wave in radians. The waveform is shifted along the x axis 
  // by this amount. 0 is a sine wave, pi/2 is a cosine. 
  const float& phase() const { return phase_; }
  
  void set_frequency( float new_frequency ) { frequency_ = new_frequency; }
  void set_phase( float new_phase ) { phase_ = new_phase; }
  void set_minimum( byte new_minimum );
  void set_maximum( byte new_maximum );

  // The most recently calculated value of the wave
  byte value() const { return value_; }
  
  // Advances the wave one step and returns the newly calculated final value
  byte next_value();
  
  // Prints the wave values to the serial console. Call Serial.begin before using.
  void test();

private:
  void update_range() { range_ = (maximum_ - minimum_) / 2; }
  
  float frequency_;
  float phase_;
  float minimum_;
  float maximum_;
  
  float range_; // half the amplitude
  float value_;
  float cnt_;
};