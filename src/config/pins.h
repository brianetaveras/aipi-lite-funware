#pragma once


#define ACTION_BTN_1_PIN 42
#define ACTION_BTN_2_PIN 43


#define BACKLIGHT_PIN 3


// User_Setup.h for ST7735S SPI display
// This file is for a 1.44" 128x128 pixel display
// You may need to adjust the pin numbers below to match your wiring

#define TFT_WIDTH 128
#define TFT_HEIGHT 128

#define Pin_LCD_MOSI 17 
#define Pin_LCD_SCLK 16   
#define Pin_LCD_CS   15   
#define Pin_LCD_DC   7      
#define Pin_LCD_RST  18 

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SPI_FREQUENCY  8000000
#define SPI_READ_FREQUENCY  20000000



