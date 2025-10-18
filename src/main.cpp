#include <Arduino.h>

#include "config/pins.h"
#include "modules/Display.h"
#include "modules/Network.h"
#include "modules/Filesystem.h"
#include "modules/DevicePreferences.h"

volatile bool buttonPressed = false;

void IRAM_ATTR handleButtonPress()
{

  buttonPressed = !buttonPressed;
  wakeScreen();
}

void setup()
{
  Serial.begin(115200);

  setupDisplay();

  setupDevicePreferences();
  setupFileSystem();
  delay(2000); // just to see the boot logo
  setupNetwork();

  pinMode(ACTION_BTN_1_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ACTION_BTN_1_PIN), handleButtonPress, FALLING);
}

void loop()
{
  displayLoop();
  networkLoop();
}
