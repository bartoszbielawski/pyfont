#include "FakeLedControl.h"
#include "SDD.hpp"
#include <iostream>

using namespace std;

SDD::SDD(FakeLedControl &ledControl):
  ledControl(ledControl),
  buffer(ledControl.getDeviceCount() * 8),
  physicalDisplayLen(ledControl.getDeviceCount() * 8)
{
    for (int i = 0; i < ledControl.getDeviceCount(); ++i)
    {
      ledControl.shutdown(i, false);
      ledControl.clearDisplay(i);
    }
}

bool SDD::tick()
{
   switch (state)
   {
     case STATE::START:
      if (!--delayCounter)
      {
        state = STATE::MIDDLE;
      }
      return false;
    
     case STATE::MIDDLE:
     {
      startColumn += columnIncrement;
      refreshDisplay();

      bool done = (buffer.size() - startColumn) < physicalDisplayLen;
      if (done)
      {
        state = STATE::END;
        delayCounter = endDelay;
      }
      return false;
     }

     case STATE::END:
        delayCounter--;
        if (delayCounter == 0)
        {
          state = STATE::START;
          delayCounter = endDelay;
          startColumn = 0;
          return true;
        }
       return false;
   }

   return true;
}

void SDD::refreshDisplay()
{
  int physicalDisplayLen = 8 * ledControl.getDeviceCount();
  
  for (int  i = 0; i < physicalDisplayLen; ++i)
  {
    ledControl.setColumn(i / 8, i % 8, buffer[i+startColumn]);
  }

  ledControl.print();
}

void SDD::renderString(const std::string &message, const PyFont& font)
{
  int physicalDisplayLen = 8 * ledControl.getDeviceCount();
  size_t len = calculateRenderedLength(font, message.c_str());
  startColumn = 0;

  //here we make difference between a text that fits in the display and a text
  //that has to be scrolled
  if (len <= physicalDisplayLen)
  {
    buffer.resize(len, 0);                              //resize and zero
    int margin = (physicalDisplayLen - len + 1) / 2;    //calculate margin with rounding
    renderText(font, message.c_str(), buffer.data() + margin, len);

    state = STATE::END;
    delayCounter = endDelay;

    refreshDisplay();
    return;
  }

  //just change the size, the values will be initialized anyway when rendering
  buffer.resize(len); 
  renderText(font, message.c_str(), buffer.data(), len);

  state = STATE::START;
  delayCounter = endDelay;
  
  refreshDisplay();
}