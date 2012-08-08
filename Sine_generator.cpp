#include "Sine_generator.h"


///////////////////////////////////////////////////////////

Sine_generator::Sine_generator( byte min_in, byte max_in, float frequency, float phase )
 : minimum_(min_in), maximum_(max_in), frequency_(frequency), phase_(phase), 
  value_(0), cnt_(0)
{
  update_range();
}

///////////////////////////////////////////////////////////

void Sine_generator::set_minimum( byte new_minimum )
{
  minimum_ = new_minimum;
  if ( minimum_ > maximum_ )
  {
    maximum_ = minimum_;
  }
  update_range();
}

///////////////////////////////////////////////////////////

void Sine_generator::set_maximum( byte new_maximum )
{
  maximum_ = new_maximum;
  if ( maximum_ < minimum_ )
  {
    minimum_ = maximum_;
  }
  update_range();
}

///////////////////////////////////////////////////////////
 
byte Sine_generator::next_value()
{
  value_ = ( sin( (PI*2) * ( cnt_ * frequency_ / range_ ) + phase_ ) + 1 ) * range_ + minimum_;
  ++cnt_;
  return value_;
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