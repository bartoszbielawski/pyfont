#ifndef PYFONT_H
#define PYFONT_H

#include <cstdint>
#include <utility>
#include <cassert>
#include <vector>

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
        assert(ch < chars);
        return sizes[ch];
    }

    std::pair<const uint8_t*, uint8_t> getChar(uint8_t ch) const
    {
        assert(ch < chars);
        return std::make_pair(data + offsets[ch], sizes[ch]);
    }
};


uint32_t             calculateStringLen(const PyFont& f, const char* str, uint8_t interCharSpace = 1);
std::vector<uint8_t>       renderString(const PyFont& f, const char* str, uint8_t interCharSpace = 1);

#endif //PYFONT_H
