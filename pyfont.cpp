#include "pyfont.h"

#include <algorithm>
#include <iterator>
#include <cstring>

uint32_t calculateStringLen(const PyFont& f, const char* str, uint8_t interCharSpace)
{
    uint32_t totalLen = 0;
    while (char c = *str++)
    {
        totalLen +=  f.getCharSize(c - f.baseChar);
        totalLen += interCharSpace;
    }
    return totalLen;
}

std::vector<uint8_t>  renderString(const PyFont& f, const char* str, uint8_t interCharSpace)
{
  std::vector<uint8_t> result;

  size_t len = strlen(str);
  result.reserve(len * 5);    //reserve just in case

  while (char c = *str++)
  {
    auto charData = f.getChar(c-f.baseChar);
    std::copy(charData.first, charData.first + charData.second, back_inserter(result));
    result.push_back(0);    //interCharSpace == 1
  }

  return result;
}
