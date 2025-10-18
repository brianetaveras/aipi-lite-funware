#pragma once

#include <FS.h>
#include "Filesystem.h"
#include <LittleFS.h>
#include <Arduino.h>

bool fileExists(const char* path) {
    return LittleFS.exists(path);
}

File openFile(const char* path, const char* mode) {
    return LittleFS.open(path, mode);
}

void setupFileSystem() {
    Serial.println("Mounting LittleFS...");
    if (!LittleFS.begin()) {
        Serial.println("[ERROR] LittleFS mount failed!");
        Serial.println("If using PlatformIO, ensure /data exists in project root and run: pio run -t uploadfs");
        Serial.println("If using custom partition table, ensure LittleFS size is sufficient");
        Serial.println("If using SPIFFS, switch to LittleFS in code and platformio.ini");
        Serial.println("Listing files in LittleFS root:");
        File root = LittleFS.open("/");
        if (root && root.isDirectory()) {
            File file = root.openNextFile();
            bool found = false;
            while (file) {
                Serial.print("- ");
                Serial.print(file.name());
                Serial.print(" (size: ");
                Serial.print(file.size());
                Serial.println(")");
                file = root.openNextFile();
                found = true;
            }
            if (!found) {
                Serial.println("No files found in LittleFS root.");
            }
        } else {
            Serial.println("Could not open root directory or not a directory.");
        }
    } else {
        Serial.println("LittleFS mounted successfully.");
    }
}
