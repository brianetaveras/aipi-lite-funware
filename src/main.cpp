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

  // This is here to make sure the device stays powered on using the battery.
  // I'll probably move this to a battery module later when I start showing battery status. :)
  pinMode(GPIO_NUM_10, OUTPUT);
  digitalWrite(GPIO_NUM_10, HIGH);

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
