#include "config/pins.h"
#include <Arduino.h>
#include "modules/Display.h"
#include "modules/DevicePreferences.h"

volatile bool mainButtonPressed = false;
static unsigned long mainButtonPressTime = 0;

volatile bool secondaryButtonPressed = false;
volatile unsigned long secondaryButtonPressTime = 0;
#define LONG_PRESS_DURATION 10000 // 10 seconds in milliseconds

void IRAM_ATTR handleButtonOnePress()
{

    mainButtonPressed = true;
    mainButtonPressTime = millis();
    wakeScreen();
    Serial.printf("Screen dimensions are %dx%d\n", lcd.width(), lcd.height());
}

void IRAM_ATTR handleButtonTwoPress()
{
    secondaryButtonPressed = true;
    secondaryButtonPressTime = millis();
    wakeScreen();
}

void setupInput()
{

    pinMode(ACTION_BTN_1_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ACTION_BTN_1_PIN), handleButtonOnePress, FALLING);

    pinMode(ACTION_BTN_2_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ACTION_BTN_2_PIN), handleButtonTwoPress, FALLING);
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
    unsigned long heldTime = currentTime - mainButtonPressTime;
    if (heldTime >= LONG_PRESS_DURATION)
    {
        onButtonLongPress();
        mainButtonPressed = false; // Reset the flag after handling long press
    }
}

void inputLoop()
{
    checkButtonLongPress();
    if (mainButtonPressed && digitalRead(ACTION_BTN_1_PIN) == HIGH)
    {
        mainButtonPressed = false;
        mainButtonPressTime = 0;
    }
    if (secondaryButtonPressed && digitalRead(ACTION_BTN_2_PIN) == HIGH)
    {
        secondaryButtonPressed = false;
        secondaryButtonPressTime = 0;
    }
}