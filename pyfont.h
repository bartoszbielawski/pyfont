#ifndef PYFONT_H
#define PYFONT_H

#include <stdint.h>

struct PyFont
{
    PyFont(uint8_t chars, uint8_t baseChar, const uint8_t* data, const uint16_t* offsets, const uint8_t* sizes):
        chars(chars), baseChar(baseChar), data(data), offsets(offsets), sizes(sizes) {}
    uint8_t chars;
    uint8_t baseChar;
    const uint8_t* data;
    const uint16_t* offsets;
    const uint8_t* sizes;

    uint8_t getCharSize(char ch) const
    {
        return sizes[ch-baseChar];
    }

    const uint8_t* getCharData(char ch) const
    {
      return data + offsets[ch-baseChar];
    }
};


int  renderString(const PyFont& f, const char* str, uint8_t interCharSpace, uint8_t* output, int size);

#endif //PYFONT_H

