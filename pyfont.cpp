#include "pyfont.h"

int renderText(const PyFont& f, const char* text, uint8_t* output, int maxSize)
{
  int outputLen = 0;

  while (char c = *text++)
  {
    uint8_t        size = f.getCharSize(c);
    const uint8_t* ptr  = f.getCharData(c);

    for (uint8_t j = 0; j < size; j++)
    {
      *output++ = ptr[j];
      outputLen++;
      if (outputLen >= maxSize)
        return outputLen;
    }

    *output++ = 0;
    outputLen++;
    if (outputLen >= maxSize)
      return outputLen;
  }

  return outputLen;
}
