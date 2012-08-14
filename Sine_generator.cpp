#include "Sine_generator.h"


///////////////////////////////////////////////////////////

Sine_generator::Sine_generator( byte min_in, byte max_in, float frequency, float phase )
 : Oscillating_generator( min_in, max_in, frequency ), phase_(phase)
{}

void Sine_generator::set( float new_minimum, float new_maximum, float new_frequency, float new_phase )
{
  set_phase( new_phase );
}

///////////////////////////////////////////////////////////

void Sine_generator::update_value()
{
  if ( range_ != 0. )
  {
    raw_value_ = ( sin( (PI*2) * ( cnt_ * (frequency_+audio_level_)/MAX_LEVEL ) + phase_ ) + 1 ) * range_ + minimum_;
  }
  ++cnt_;
}

///////////////////////////////////////////////////////////

Linear_generator::Linear_generator( Wave_type type, byte minimum, byte maximum, float frequency, byte start_value )
  : Oscillating_generator( minimum, maximum, frequency ), type_(type), direction_(1)
{
  raw_value_ = start_value <= maximum && start_value >= minimum ? start_value/MAX_LEVEL : minimum/MAX_LEVEL;
  step_size_ = range_ / MAX_LEVEL;
}

///////////////////////////////////////////////////////////

void Linear_generator::update_value()
{
  if ( range_ != 0. )
  {
    raw_value_ += step_size_*(frequency_+audio_level_)*direction_;
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

Square_generator::Square_generator( byte minimum, byte maximum, float frequency, uint16_t on_cnt, uint16_t off_cnt, bool start_on )
  : Oscillating_generator( minimum, maximum, frequency ), 
    on_(start_on), on_cnt_(on_cnt), off_cnt_(off_cnt)
{}

///////////////////////////////////////////////////////////

void Square_generator::update_value()
{
  if ( on_ && cnt_ > on_cnt_ || !on_ && cnt_ > off_cnt_ )
  {
    on_ = !on_;
    cnt_ = 0;
  }
  raw_value_ = on_ ? maximum_ : minimum_;
  cnt_ += (frequency_+audio_level_);
}


///////////////////////////////////////////////////////////

White_noise_generator::White_noise_generator( byte minimum, byte maximum, uint16_t minimum_spacing, uint16_t maximum_spacing, byte baseline_value )
  : Oscillating_generator( minimum, maximum, 1 ), min_spacing_(minimum_spacing), max_spacing_(maximum_spacing+1),
  next_cnt_(0), cnt_(0), baseline_((float)baseline_value/MAX_LEVEL)
 {}
 
///////////////////////////////////////////////////////////

void White_noise_generator::update_value()
{
  if ( range_ != 0 )
  {
    if ( cnt_ == next_cnt_ )
    {
      raw_value_ = minimum_ + (double)rand()/(double)RAND_MAX * range_ * 2;
      next_cnt_ = random( min_spacing_, max_spacing_ );
      cnt_ = 0;
    }
    else
    {
      raw_value_ = baseline_;
      ++cnt_;
    }
  }
}
