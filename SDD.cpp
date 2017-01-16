#include "FakeLedControl.h"
#include "SDD.hpp"
#include <iostream>

using namespace std;

SDD::SDD(FakeLedControl &ledControl):
  ledControl(ledControl),
  buffer(ledControl.getDeviceCount() * 8)
{
    for (int i = 0; i < ledControl.getDeviceCount(); ++i)
    {
      ledControl.shutdown(i, false);
      ledControl.clearDisplay(i);
    }
}

bool SDD::tick()
{
    int physicalDisplayLen = 8 * ledControl.getDeviceCount();

    switch (state)
    {
      case STATE::START:
        cycleCounter++;
        if (cycleCounter >= 5)
        {
          state = STATE::MIDDLE;
          cycleCounter = 5;
        }
        ledControl.print();
        return false;
      
      case STATE::MIDDLE:
      {
        //zero the array
        for (auto& e: buffer)
          e = 0;

        messageIndex++;
        int len = ::renderText(*pf, message.c_str() + messageIndex, buffer.data(), physicalDisplayLen);

        if (len < physicalDisplayLen)
        {
          state = STATE::END;
          cycleCounter = 0;
        }

        refreshDisplay();
      }
      return false;

      case STATE::END:
        cycleCounter++;
        if (cycleCounter == 5)
        {
          state = STATE::START;
          cycleCounter = 0;
          return true;
        }
        ledControl.print();
        break;

    }

    return false;
}

void SDD::refreshDisplay()
{
  int physicalDisplayLen = 8 * ledControl.getDeviceCount();

  for (int  i = 0; i < physicalDisplayLen; ++i)
  {
    ledControl.setColumn(i / 8, i % 8, buffer[i]);
  }

  ledControl.print();
}

void SDD::renderString(const std::string &message, const PyFont& font)
{
  this->message = message;
  messageIndex = 0;
  pf = &font;
  cycleCounter = 0;
  state = STATE::START;

  int physicalDisplayLen = 8 * ledControl.getDeviceCount(); 
  int len = ::renderText(*pf, message.c_str() + messageIndex, buffer.data(), physicalDisplayLen);

  refreshDisplay();

}