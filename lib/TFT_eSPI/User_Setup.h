// User_Setup.h for ST7735S SPI display
// Edit pin numbers below to match your wiring


#define ST7735S_DRIVER
#define TFT_WIDTH 128
#define TFT_HEIGHT 128

// Pinout matching ESP-IDF config:
// MOSI: 17, SCLK: 16, CS: 15, DC: 7, RST: 18
#define TFT_MOSI 17 
#define TFT_SCLK 16   
#define TFT_CS   15   
#define TFT_DC   7      
#define TFT_RST  18 

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SPI_FREQUENCY  8000000
// #define SPI_READ_FREQUENCY  20000000

// Optional: adjust pins above for your board
