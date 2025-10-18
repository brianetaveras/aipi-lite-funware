#include "config/pins.h"
#include <Arduino.h>
#include "modules/Display.h"
#include "modules/DevicePreferences.h"

volatile bool mainButtonPressed = false;
static unsigned long buttonPressDuration = 0;
#define LONG_PRESS_DURATION 10000 // 10 seconds in milliseconds


void IRAM_ATTR handleButtonPress()
{

    mainButtonPressed = true;
    buttonPressDuration = millis();
    wakeScreen();
}

void setupInput()
{

    pinMode(ACTION_BTN_1_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ACTION_BTN_1_PIN), handleButtonPress, FALLING);
}
void onButtonLongPress()
{
    eraseNVS();
}


void checkButtonLongPress()
{
    if (mainButtonPressed == false)
    {
        return;
    }

    unsigned long currentTime = millis();
    unsigned long heldTime = currentTime - buttonPressDuration;
    if (heldTime >= LONG_PRESS_DURATION)
    {
        onButtonLongPress();
        mainButtonPressed = false; // Reset the flag after handling long press
    }
}

void inputLoop()
{
    checkButtonLongPress();
    if (mainButtonPressed && digitalRead(ACTION_BTN_1_PIN) == HIGH) {
        mainButtonPressed = false;
        buttonPressDuration = 0;
    }
}