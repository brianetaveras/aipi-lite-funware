#include "config/pins.h"
#include <Arduino.h>
#include "modules/Display.h"

volatile bool mainButtonPressed = false;

void IRAM_ATTR handleButtonPress()
{

    mainButtonPressed = !mainButtonPressed;
    wakeScreen();
}

void setupInput()
{

    pinMode(ACTION_BTN_1_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ACTION_BTN_1_PIN), handleButtonPress, FALLING);
}

void inputLoop()
{
    // Placeholder for input handling logic
}
