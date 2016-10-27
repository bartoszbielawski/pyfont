#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>
#include <cstdio>
#include <array>
#include <vector>
#include <memory>

class Display
{
    public:
        Display(uint32_t X, uint32_t Y, char c):
            X(X), Y(Y), c(c), data(new bool[X*Y])
        {

        }

        void setPixel(uint16_t x, uint16_t y, bool state)
        {
            if (x >= X)
                return;
            if (y >= Y)
                return;

            uint32_t offset = y*X + x;

            data[offset] = state;
        }

        void clear()
        {
            phase = 0;
            for (int y = 0; y < Y; y++)
                for (int x = 0; x < X; x++)
                    data[y*X+x] = false;

        }

        uint16_t getX() {return X;}
        uint16_t getY() {return Y;}

        void wrap()
        {
            phase++;
        }

        void print()
        {
            for (int y = 0; y < Y; y++)
            {
                for (int x = 0; x < X; x++)
                {
                    uint16_t wrappedX = (x + phase) % X;
                    char p = data[y*X + wrappedX] ? c: ' ';

                    printf("%c", p);
                }
                printf("\n");
            }
        }

    private:
        uint16_t X;
        uint16_t Y;
        char     c;
        uint16_t phase;

        std::unique_ptr<bool[]> data;
        //std::array<std::array<bool, X>, Y> data;
        //bool data[X][Y];
};

#endif //DISPLAY_H
