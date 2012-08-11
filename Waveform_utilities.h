#ifndef WAVEFORM_UTILITIES_H
#define WAVEFORM_UTILITIES_H

// Get the product of the next values of the 2 generators
byte next_convolved_value( Waveform_generator* a, Waveform_generator* b )
{
  return ( a->next_raw_value() * b->next_raw_value() ) * MAX_LEVEL;
}

// Average together the two colors (not as good as doing it w/the generators
// cuz of rounding errors)
rgbInfo_t convolve( rgbInfo_t a, rgbInfo_t b )
{
  return rgbInfo_t(
    (a.r + b.r) / 2,
    (a.g + b.g) / 2,
    (a.b + b.b) / 2
  );
}

// Gets the next RGB value from the 3 generators
rgbInfo_t get_next_rgb( Waveform_generator* r, Waveform_generator* g, Waveform_generator* b )
{
  return rgbInfo_t( r->next_value(), g->next_value(), b->next_value() );
}

#endif