#ifndef WAVEFORM_GENERATOR_H
#define WAVEFORM_GENERATOR_H

#include "Arduino.h"
#define PI 3.14159
#define MAX_LEVEL 255

// Base waveform generator class. The generators take parameters in [0,255] range
// but internally represent themselves as floats in the range [0,1] so you can 
// access those raw values too (helpful for convolving waveforms)
class Waveform_generator
{
public:
  // The most recently calculated value of the wave (range [0,MAX_LEVEL])
  byte value() const { return raw_value_*MAX_LEVEL; }
  
  // The most recently calculated value of the wave (range [0,1])
  float raw_value() const { return raw_value_; }
  
  // Advances the wave one step and returns the newly calculated final value (range [0,MAX_LEVEL])
  byte next_value();
  
  // Advances the wave one step and returns the newly calculated final value (range [0,1])
  float next_raw_value();
  
  // Sets the current audio level on a [0,1] scale
  void set_audio_level( float level );

protected:
  Waveform_generator() : raw_value_(0), audio_level_(0) {}
  Waveform_generator(float val) : raw_value_(val), audio_level_(0) {}
  
  float raw_value_;
  float audio_level_;
  
  // Advances the wave one step
  virtual void update_value() = 0;
};



// Base class for generators that range between a min and max
class Oscillating_generator : public Waveform_generator
{
public:
  Oscillating_generator( byte min_in, byte max_in, float frequency );
   
  // The wave's lower bound on the Y axis [0,255]
  float minimum() const { return minimum_*MAX_LEVEL; }
  
  // The wave's upper bound on the Y axis [0,255]
  float maximum() const { return maximum_*MAX_LEVEL; }
  
  // Frequency multiplier. This is a factor, not a time unit (since the wave's 
  // actual frequency in milliseconds depends on how often next_value is called).
  const float& frequency() const { return frequency_; }
  
  void set_minimum( float new_minimum ); // [0,255]
  void set_maximum( float new_maximum ); // [0,255]
  void set_frequency( float new_frequency ) { frequency_ = new_frequency; }
  
  // Prints the wave values to the serial console. Call Serial.begin before using.
  void test();
  
protected:
  float minimum_, maximum_;
  float range_; // half the amplitude
  float frequency_;
  
  float cnt_;
  
  void update_range();
};



// A generator that just returns 0 all the time
class Empty_waveform : public Waveform_generator
{
public:
  Empty_waveform() : Waveform_generator(0) {}
  
protected:
  // from Waveform_generator
  void update_value() {}
};




// A generator that returns a constant
class Constant_waveform: public Waveform_generator
{
public:
  Constant_waveform( byte value ) : 
    Waveform_generator( (float)value/MAX_LEVEL) {}
protected:
  void update_value() {}
};

#endif