#include <Arduino.h>

#include "config/pins.h"
#include "modules/Display.h"
#include "modules/Network.h"
#include "modules/Filesystem.h"
#include "modules/DevicePreferences.h"
#include "modules/InputModule.h"

void setup()
{
  Serial.begin(115200);
  setupInput();
  setupDisplay();
  setupDevicePreferences();
  setupFileSystem();
  delay(2000); // just to see the boot logo
  setupNetwork();
}

void loop()
{
  inputLoop();
  displayLoop();
  networkLoop();
}
