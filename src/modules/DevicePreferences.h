#pragma once

#include <Arduino.h>
#include "nvs_flash.h"
#include <Preferences.h>


extern Preferences devicePrefrerences;

extern String wifi_ssid;
extern String wifi_password;

void setupDevicePreferences();
void setNetworkPreferences(const String &ssid, const String &password);
void eraseNVS();