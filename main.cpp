#include "myTestFont.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "display.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
     return 0;

    uint32_t len = calculateStringLen(myTestFont::font, argv[1]);

    char* c = argv[1];


    auto v = renderString(myTestFont::font, c);

    for (auto& s: v)
    {
      for (int  i = 0; i < 8; i++)
      {
        printf("%c", s & 0x80 ? '#': ' ');
        s <<= 1;
      }
      printf("\n");
    }


    return 0;
}
