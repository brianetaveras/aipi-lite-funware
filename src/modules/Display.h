#include "config/pins.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

extern Adafruit_ST7735 lcd;

void setupDisplay();
void displayLoop();
void wakeScreen();
void displayCenterAnnouncement(const String &message);