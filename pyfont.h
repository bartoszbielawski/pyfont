#ifndef PYFONT_H
#define PYFONT_H

#include <cstdint>
#include <utility>
#include <cassert>


struct PyFont
{
    PyFont(uint8_t chars, const uint8_t* data, const uint16_t* offsets, const uint8_t* sizes):
        chars(chars), data(data), offsets(offsets), sizes(sizes) {}
    uint8_t chars;
    const uint8_t* data;
    const uint16_t* offsets;
    const uint8_t* sizes;

    uint8_t getCharSize(char ch) const
    {
        assert(ch < chars);
        return sizes[ch];
    }

    std::pair<const uint8_t*, uint8_t> getChar(uint8_t ch) const
    {
        assert(ch < chars);
        return std::make_pair(data + offsets[ch], sizes[ch]);
    }
};


uint32_t calculateStringLen(const PyFont& f,uint8_t baseChar, const char* str, uint8_t interCharSpace)
{
    uint32_t totalLen = 0;
    while (char c = *str++)
    {
        totalLen +=  f.getCharSize(c - baseChar);
        totalLen += interCharSpace;
    }
    return totalLen;
}


#endif //PYFONT_H
