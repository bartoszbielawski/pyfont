#include "pyfont.h"

int  renderString(const PyFont& f, const char* str, uint8_t interCharSpace, uint8_t* output, int size)
{
  int outputSize = 0;
  
  while (char c = *str++)
  {
    const uint8_t* ptr = f.getCharData(c);
    uint8_t         cs = f.getCharSize(c);
    
    for (int s = 0; s < cs; s++)
    {
      outputSize++;
      *output++ = ptr[s];
    }

    
    *output++ = 0;    //interspace 1, ignores the parameter so far
    outputSize++;
  }

 
  return outputSize;
}


