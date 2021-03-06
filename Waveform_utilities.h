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


byte summed_value( Waveform_generator* a, Waveform_generator* b )
 {
   float rval = a->raw_value() + b->raw_value();
   if ( rval > 1.0 )
   {
     rval = 1.0;
   }
   if ( rval < 0.0 )
   {
     rval = 0.0;
   }
   return rval * MAX_LEVEL;
 }


byte next_summed_value( Waveform_generator* a, Waveform_generator* b )
 {
   a->next_raw_value();
   b->next_raw_value();
   return summed_value(a,b);
 }
 
 
rgbInfo_t rgb_scaled_summed_value( const float& red, const float& green, const float& blue, float summand)
{
 float max = red > green ? red : green;
  max = max > blue ? max : blue;
  summand = 1-max < summand ? 1-max : summand;
  float multiplier = 1 + summand/max;
  
  return rgbInfo_t(
    red*multiplier*MAX_LEVEL, green*multiplier*MAX_LEVEL, blue*multiplier*MAX_LEVEL
  );
}
 
// summand should be a float [0,1] 
rgbInfo_t rgb_scaled_summed_value( Waveform_generator* r, Waveform_generator* g, Waveform_generator* b, const float& summand )
{
  float red = r->next_raw_value();
  float green = g->next_raw_value();
  float blue = b->next_raw_value();
  return rgb_scaled_summed_value(red,green,blue,summand);
} 
 
// Used for transitions between routines. Multiplier is a number in [0,1] that
// specifies the proportion of the interpolation that's completed (i.e. the 
// proportion of the return value that should come from the to argument)
float interpolated_value( const float& from, const float& to, float multiplier )
{
  if ( multiplier < 0 ) 
  {
    multiplier = 0;
  }
  else if ( multiplier > 1 )
  {
    multiplier = 1;
  }
  float val = from * (1-multiplier) + to * multiplier;
  return val;
}

 
byte get_luminance( const float& r, const float& g, const float& b )
{
  // If this needs to be optimized later, (R+R+B+G+G+G)/6 is a decent approximation
  // although it slightly over-weights red
  return ( 0.2126 * r + 0.7152 * g + 0.0722 * b ) * MAX_LEVEL;
}
 
 
rgbInfo_t next_greyscale_value( const float& r, const float& g, const float& b )
{
  byte luminance = get_luminance( r, g, b );
  return rgbInfo_t( luminance, luminance, luminance );
}
 
 
rgbInfo_t next_greyscale_value( Waveform_generator* a, Waveform_generator* b, Waveform_generator* c )
{
  return next_greyscale_value( a->next_raw_value(), b->next_raw_value(), c->next_raw_value() );
}
 

rgbInfo_t fade_color( rgbInfo_t color, float fade_fraction )
{
  color.r *= fade_fraction;
  color.g *= fade_fraction;
  color.b *= fade_fraction;
  return color;
}


#endif