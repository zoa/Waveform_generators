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
  
  virtual byte value() const = 0;
  // Advances the wave one step and returns the newly calculated final value (range [0,MAX_LEVEL])
  virtual byte next_value() = 0;
  
  // The most recently calculated value of the wave (range [0,1])
  virtual float raw_value() const = 0;
  
  // Advances the wave one step and returns the newly calculated final value (range [0,1])
  virtual float next_raw_value() = 0;
};



// Base class for generators that range between a min and max
class Oscillating_generator : public Waveform_generator
{
public:
  Oscillating_generator( byte min_in, byte max_in );
    
  void set_minimum( float new_minimum ); // [0,255]
  void set_maximum( float new_maximum ); // [0,255]
  
  // from Waveform_generator
  byte value() const { return scaled_value_; }
  float raw_value() const { return raw_value_; }
  
protected:
  float minimum_;
  float maximum_;
  float range_; // half the amplitude
  float raw_value_;
  
  byte scaled_value_; // [0,255]
  
  float cnt_;
  
  void update_range();
};



// A generator that just returns 0 all the time
class Empty_waveform : public Waveform_generator
{
public:
  // from Waveform_generator
  byte value() const { return 0; }
  byte next_value() { return 0; }
  float raw_value() const { return 0; }
  float next_raw_value() { return 0; }
};




// A generator that returns a constant
class Constant_waveform: public Waveform_generator
{
public:
  Constant_waveform( byte value ) : 
    raw_value_( (float)value/MAX_LEVEL) {}
    
      // from Waveform_generator
  byte value() const { return raw_value_*MAX_LEVEL; }
  byte next_value() { return raw_value_*MAX_LEVEL; }
  float raw_value() const { return raw_value_; }
  float next_raw_value() { return raw_value_; }
  
private:
  float raw_value_;
};

#endif