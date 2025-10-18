# AIPI-Lite Funware

I started this project with to explore adding a custom software to the XOROGIN AI PI-LITE board. I am not a  C++ developer so there may be a lot of bugs and less than ideal implementations.

To get the board to boot mode the first time you flash, you need to remove the 4 back screws and bress the button behind the screen while plugging-in the device. My plan is to make a tamagochi-like device, but make it as unhinged as I can. This is not a serious project, just a fun experiment. 


## Done:
- Display compatibility through Adafruit's GFX lib [x]
- Network selection through web portal and access point [x]
- Filesystem (to store web static assets and serve wifi portal) [x]
- Persistent Preference to save wifi info [x]


## Getting Started
1. **Install PlatformIO** (VS Code recommended)
2. **Clone this repo**
3. **Configure your board** in `platformio.ini` (default: ESP32S3-WROOM-1)
4. **Upload filesystem:**
   ```
   pio run -t uploadfs --upload-port /dev/ttyACM0
   ```
5. **Build and upload firmware:**
   ```
   pio run --target upload --upload-port /dev/ttyACM0
   ```
6. **Connect to device AP:**
   - SSID: `BSoft_Setup`
   - Password: (if set)
   - Navigate to `http://192.168.4.1` to configure WiFi

## GZIP Static Files
To enable GZIP for static assets:
```sh
cd data
gzip -k index.html nes.min.css fonts/PressStart2P.woff2
```
Re-upload the filesystem after gzipping.


## Credits
- Adafruit libraries (GFX, BusIO, seesaw, ST77xx)
- PlatformIO
- ESP32 Arduino framework

## Warnings/Disclaimers

Use this at your own risk, this is a fun codebase I'm using to learn ESP32 wizardry