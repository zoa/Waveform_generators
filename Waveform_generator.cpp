#include "Waveform_generator.h"


///////////////////////////////////////////////////////////
 
byte Waveform_generator::next_value()
{
  update_value();
  return raw_value_*MAX_LEVEL;
}

///////////////////////////////////////////////////////////
 
float Waveform_generator::next_raw_value()
{
  update_value();
  return raw_value_;
}

///////////////////////////////////////////////////////////

void Waveform_generator::set_audio_level( float level )
{
  audio_level_ = level;
}

///////////////////////////////////////////////////////////

Oscillating_generator::Oscillating_generator( byte min_in, byte max_in, float frequency ) 
    : cnt_(0), frequency_(frequency)
{
  set_minimum(min_in);
  set_maximum(max_in);
  set_frequency(frequency);
}

///////////////////////////////////////////////////////////

void Oscillating_generator::set_minimum( float new_minimum )
{
  minimum_ = new_minimum / MAX_LEVEL;
  if ( minimum_ > maximum_ )
  {
    set_maximum(new_minimum);
  }
  update_range();
}

///////////////////////////////////////////////////////////

void Oscillating_generator::set_maximum( float new_maximum )
{
  maximum_ = new_maximum / MAX_LEVEL;
  if ( maximum_ < minimum_ )
  {
    set_minimum(new_maximum);
  }
  update_range();
}

///////////////////////////////////////////////////////////

void Oscillating_generator::update_range() 
{ 
  range_ = (maximum_ - minimum_) / 2; 
  if ( range_ == 0 )
  {
    raw_value_ = minimum_;
  }
}


///////////////////////////////////////////////////////////

void Oscillating_generator::test()
{
  for ( uint16_t i = 0; i < 1000; ++i )
  {
    update_value();
    Serial.println(next_value());
  }
  delay(1000);
}