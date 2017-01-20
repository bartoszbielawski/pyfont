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


int renderText(const PyFont& f, const char* text, uint8_t* output, int maxSize);
int calculateRenderedLength(const PyFont& f, const char* text);

#endif //PYFONT_H
