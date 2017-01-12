#include "FakeLedControl.h"
#include "SDD.hpp"
#include <iostream>

using namespace std;

SDD::SDD(FakeLedControl &ledControl):
  ledControl(ledControl),
  buffer(ledControl.getDeviceCount() * 8, 0)
{
    for (int i = 0; i < ledControl.getDeviceCount(); ++i)
    {
      ledControl.shutdown(i, false);
      ledControl.clearDisplay(i);
    }
}

bool SDD::tick()
{
    int physicalDisplayLen = ledControl.getDeviceCount() * 8;

    for (int  i = 0; i < physicalDisplayLen; ++i)
    {
      ledControl.setColumn(i / 8, i % 8, buffer[i]);
    }

    ledControl.print();
    return true;
}

void SDD::renderString(const std::string &message, const PyFont& font)
{
  int len = ::renderText(font, message.c_str(), buffer.data(), buffer.size());
}
