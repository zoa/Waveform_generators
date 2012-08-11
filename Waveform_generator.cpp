#include "Waveform_generator.h"

///////////////////////////////////////////////////////////

Oscillating_generator::Oscillating_generator( byte min_in, byte max_in ) 
    : raw_value_(0), scaled_value_(0), cnt_(0) 
{
  set_minimum(min_in);
  set_maximum(max_in);
}

///////////////////////////////////////////////////////////

void Oscillating_generator::set_minimum( float new_minimum )
{
  minimum_ = new_minimum / MAX_LEVEL;
  if ( minimum_ > maximum_ )
  {
    maximum_ = minimum_;
  }
  update_range();
}

///////////////////////////////////////////////////////////

void Oscillating_generator::set_maximum( float new_maximum )
{
  maximum_ = new_maximum / MAX_LEVEL;
  if ( maximum_ < minimum_ )
  {
    minimum_ = maximum_;
  }
  update_range();
}

///////////////////////////////////////////////////////////

void Oscillating_generator::update_range() 
{ 
  range_ = (maximum_ - minimum_) / 2; 
  if ( range_ == 0 )
  {
    raw_value_ = scaled_value_ = minimum_;
  }
}