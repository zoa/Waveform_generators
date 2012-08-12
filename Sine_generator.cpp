#include "Sine_generator.h"


///////////////////////////////////////////////////////////

Sine_generator::Sine_generator( byte min_in, byte max_in, float frequency, float phase )
 : Oscillating_generator( min_in, max_in ), frequency_(frequency), phase_(phase)
{}

void Sine_generator::set( float new_minimum, float new_maximum, float new_frequency, float new_phase )
{
  set_minimum( new_minimum );
  set_maximum( new_maximum );
  set_frequency( new_frequency );
  set_phase( new_phase );
}

///////////////////////////////////////////////////////////

void Sine_generator::update_values()
{
  if ( range_ != 0. )
  {
    raw_value_ = ( sin( (PI*2) * ( cnt_ * frequency_/MAX_LEVEL ) + phase_ ) + 1 ) * range_ + minimum_;
    scaled_value_ = raw_value_ * MAX_LEVEL;
  }
  ++cnt_;
}

///////////////////////////////////////////////////////////
 
byte Sine_generator::next_value()
{
  update_values();
  return scaled_value_;
}

///////////////////////////////////////////////////////////
 
float Sine_generator::next_raw_value()
{
  update_values();
  return raw_value_;
}

///////////////////////////////////////////////////////////

void Sine_generator::test()
{
  uint16_t i = 1;
  while (i > 0)
  {
    Serial.println( next_value() );
  }
}

///////////////////////////////////////////////////////////

Linear_generator::Linear_generator( Wave_type type, byte minimum, byte maximum, byte start_value )
  : Oscillating_generator( minimum, maximum ), type_(type), direction_(1)
{
  raw_value_ = start_value <= maximum && start_value >= minimum ? start_value/MAX_LEVEL : minimum/MAX_LEVEL;
  step_size_ = range_ / MAX_LEVEL;
}

///////////////////////////////////////////////////////////

void Linear_generator::update_value()
{
  if ( range_ != 0. )
  {
    raw_value_ += step_size_*direction_;
    if ( raw_value_ > maximum_ || raw_value_ < minimum_ )
    {
      if ( type_ == SAWTOOTH )
      {
	raw_value_ = minimum_;
      }
      else
      {
	direction_ = (direction_==1) ? -1 : 1;
	raw_value_ += step_size_*direction_;
      }
    }
  }
}

///////////////////////////////////////////////////////////

byte Linear_generator::next_value()
{
  update_value();
  return raw_value_*MAX_LEVEL;
}

///////////////////////////////////////////////////////////

float Linear_generator::next_raw_value()
{
  update_value();
  return raw_value_;
}

///////////////////////////////////////////////////////////

void Linear_generator::test()
{
  for ( int i = 0; i < 1000; ++i )
  {
    Serial.println( next_value() );
  }
}

///////////////////////////////////////////////////////////