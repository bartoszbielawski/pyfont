#include "myTestFont.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "FakeLedControl.h"

using namespace std;

int main(int argc, char* argv[])
{

  if (argc < 2)
     return 0;

  char* message = argv[1];

  array<uint8_t, 4096> buffer;
  buffer.fill(0);

  int len = renderString(myTestFont::font, message, 1, buffer.data(), buffer.size());

  //prepare the "display"
  //             elems, len
  FakeLedControl<32, 8> lcdControl;

  //clear all the displays and enable them
  for (int i = 0; i < lcdControl.getDeviceCount(); ++i)
  {
    lcdControl.shutdown(i, false);
    lcdControl.clearDisplay(i);
  }

  //for each column of the display copy the rendered text into it
  uint32_t totalColumns = lcdControl.getDeviceCount() * 8;

  for (int  i = 0; i < totalColumns; ++i)
  {
    lcdControl.setColumn(i / 8, i % 8, buffer[i]);
  }

  //put the data on stdout
  lcdControl.print();

  return 0;
}
