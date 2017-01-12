#pragma once

#include <vector>
#include <bitset>
#include <stdint.h>
#include <array>
#include <stdexcept>
#include <cassert>


//This class pretends to be the LcdControl class available on Arduino.
//Some methods haven't been implemented
class FakeLedControl
{
    public:
        FakeLedControl(uint32_t displays, uint32_t displayLen = 8):
          displays(displays),
          displayLen(displayLen),
          displayEnabled(displays, false),
          columns(displays * displayLen, 0)
        {
        }

        void shutdown(uint32_t addr, bool disabled)
        {
            assert(addr < displays);
            displayEnabled[addr] = !disabled;
        }

        int getDeviceCount() const {return displays;}

        void setScanLimit(int addr, int limit)
        {
            throw std::runtime_error("Not implemented");
        }

        void setIntensity(int addr, int intensity) const
        {
        }

        void clearDisplay(int addr)
        {
            assert(addr < displays);

            for (int i = addr*displayLen; i <(addr+1)*displayLen; ++i)
            {
                columns[i] = 0;
            }
        }

        void setLed(int addr, int row, int col, bool state)
        {
            assert(addr < displays);

            uint32_t linearAddress = addr * displayLen + col;
            uint8_t& v = columns[linearAddress];

            if (state)
            {
                v |= 1<<col;
            }
            else
            {
                v &= ~(1<<col);
            }
        }

        void setRow(int addr, int row, uint8_t value)
        {
            throw std::runtime_error("Not implemented!");
        }

        void setColumn(int addr, int col, uint8_t value)
        {
            assert(addr < displays);

            uint32_t linearAddress = addr * displayLen + col;
            columns[linearAddress] = value;
        }

        void setDigit(int addr, int digit)
        {
            throw std::runtime_error("Not implemented!");
        }

        void setChar(int addr, int digit, uint8_t value, bool dp)
        {
            throw std::runtime_error("Not implemented!");
        }

        void print()
        {

            for (uint8_t mask = 0x01; mask > 0; mask <<= 1)
            {
                for (int col = 0; col < displays * displayLen; ++col)
                {
                    uint32_t displayAddress = col / displayLen;
                    uint8_t toPrint = displayEnabled[displayAddress] ? columns[col] & mask: 0;
                    toPrint = toPrint ? '#': ' ';
                    putchar(toPrint);
                }
                putchar('\n');
            }
        }

    private:
      uint32_t displays;
      uint32_t displayLen;
      std::vector<bool> displayEnabled;
      std::vector<uint8_t> columns;
};
