#include "myTestFont.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "display.h"


int main(int argc, char* argv[])
{
    if (argc < 2)
     return 0;

    uint32_t len = calculateStringLen(myTestFont::font, ' ', argv[1], 1);

    char* c = argv[1];

    Display d(len + 5, 8, '#');

    while (true)
    {
        uint16_t colIndex = 0;
        char* t = c;

        while (*t)
        {

            uint32_t index = *t++ - ' ';
            auto f = myTestFont::font.getChar(index);
            //printf("I: %d S: %d\n", index, f.second);



            for (int i = 0; i < f.second; i++)
            {
                auto col = *f.first++;

                for (int j = 0; j < 8; j++)
                {
                    d.setPixel(colIndex, j, col & 0x1);
                    col >>= 1;
                }
                colIndex++;
            }
            colIndex++;
        }

        d.print();
        d.wrap();

        usleep(200000);

    }

    return 0;
}
