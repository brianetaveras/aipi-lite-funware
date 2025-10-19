#include "Display.h"
#include "Sprites.h"

void setupPetModule()
{
    wakeScreen();
    lcd.setCursor(0, 0);
    lcd.drawBitmap(0, 0, background_sprite, 128, 128, ST7735_WHITE);

    lcd.setCursor(10, 10);
    lcd.setTextColor(ST7735_BLACK);
    lcd.setTextSize(1);
    lcd.print("Pet incoming!");
}

void petModuleLoop()
{
    // Placeholder for any future loop code for the pet module
}