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


byte next_summed_value( Waveform_generator* a, Waveform_generator* b )
 {
   float rval = a->next_raw_value() + b->next_raw_value();
   if ( rval > 1.0 )
   {
     rval == 1.0;
   }
   if ( rval < 1.0 )
   {
     rval = 1.0;
   }
   return rval * MAX_LEVEL;
 }
 
 /*
 byte get_luminance( const rgbInfo_t& color )
 {
   return get_luminance( color.r, color.g, color.b );
 }*/
 
 byte get_luminance( const float& r, const float& g, const float& b )
 {
   // If this needs to be optimized later, (R+R+B+G+G+G)/6 is a decent approximation
   // although it slightly over-weights red
   return 0.2126 * r + 0.7152 * g + 0.0722 * b;
 }
 
 
 
 rgbInfo_t next_greyscale_value( const float& r, const float& g, const float& b )
 {
   byte luminance = get_luminance( r, g, b ) * MAX_LEVEL;
   return rgbInfo_t( luminance, luminance, luminance );
 }
 
 rgbInfo_t next_greyscale_value( Waveform_generator* a, Waveform_generator* b, Waveform_generator* c )
 {
   return next_greyscale_value( a->next_raw_value(), b->next_raw_value(), c->next_raw_value() );
 }

#endif