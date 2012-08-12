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
  
  // Phase of the wave in radians. The waveform is shifted along the x axis 
  // by this amount. 0 is a sine wave, pi/2 is a cosine. 
  const float& phase() const { return phase_; }
  
  void set( float new_frequency, float new_phase, float new_minimum, float new_maximum );
  void set_phase( float new_phase ) { phase_ = new_phase; }

protected:  
  void update_value();
  
private:
  float phase_;
};




// Linear wave that either goes up from min->max and then back to 0 and up again (sawtooth)
// or from min->max->min->max ... (triangle wave)
class Linear_generator : public Oscillating_generator
{
public:
  enum Wave_type { SAWTOOTH, TRIANGLE }; // could make separate classes if more time
  
  Linear_generator( Wave_type type, byte minimum, byte maximum, float frequency, byte start_value = 0 );
  
protected:
  void update_value();
  
private:
  signed char direction_; //only for triangle waves - 1=up, -1=down
  Wave_type type_;
  float step_size_;
};


// Square wave. Unlike a normal square wave, this one lets you specify different
// on and off durations so the cycle doesn't need to be symmetrical.'
class Square_generator : public Oscillating_generator
{
public:
  Square_generator( byte minimum, byte maximum, float frequency, uint16_t on_cnt, uint16_t off_cnt, bool start_on = true );
  
protected:
  void update_value();
  
private:
  bool on_;
  float cnt_;
  uint16_t on_cnt_, off_cnt_;
};


#endif