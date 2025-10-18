#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "config/pins.h"
#include "modules/Images.h"

Adafruit_ST7735 lcd(Pin_LCD_CS, Pin_LCD_DC, Pin_LCD_MOSI, Pin_LCD_SCLK,
                    Pin_LCD_RST);

void setupDisplay()
{

    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, HIGH);

    lcd.initR(INITR_18BLACKTAB); // For 1.44" 128x128 ST7735
    lcd.fillScreen(ST7735_BLACK);
    lcd.enableDisplay(true);

    lcd.setCursor(0, 0);

    lcd.setRotation(3);

    // Show the boot logo
    lcd.drawBitmap(0, 0, boot_image, 128, 128, ST7735_WHITE);
    lcd.setCursor(40, 115);
    lcd.setTextColor(ST7735_BLACK);
    lcd.setTextSize(1);
    lcd.println("Birbsoft");
}

unsigned long lastScreenTime = 0;
const int screenTimeout = 10000;
void restScreen()
{

    if (millis() - lastScreenTime > screenTimeout)
    {
        digitalWrite(BACKLIGHT_PIN, LOW); // Turn off backlight
    }
}

void wakeScreen()
{
    digitalWrite(BACKLIGHT_PIN, HIGH);
    lastScreenTime = millis();
}

void displayLoop()
{
    restScreen();
}