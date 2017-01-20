#include "myTestFont.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "FakeLedControl.h"
#include "SDD.hpp"

using namespace std;

int main(int argc, char* argv[])
{

  if (argc < 2)
     return 0;

  char* message = argv[1];

  FakeLedControl fakeLedControl(8,8);

  SDD scrollingDisplayDriver(fakeLedControl);

  cout << "The full length: " << calculateRenderedLength(myTestFont::font, message) << endl;

  scrollingDisplayDriver.renderString(message, myTestFont::font);

  bool done = scrollingDisplayDriver.tick();

  while (!done) done = scrollingDisplayDriver.tick();
  
  return 0;
}
