#include "DevicePreferences.h"

Preferences devicePrefrerences;

String wifi_ssid;
String wifi_password;

void setupDevicePreferences()
{
    devicePrefrerences.begin("devicePrefs", false);

    if (!devicePrefrerences.isKey("wifi_ssid"))
    {
        devicePrefrerences.putString("wifi_ssid", "");
    }

    wifi_ssid = devicePrefrerences.getString("wifi_ssid");

    if (!devicePrefrerences.isKey("wifi_password"))
    {
        devicePrefrerences.putString("wifi_password", "");
    }

    wifi_password = devicePrefrerences.getString("wifi_password");

    devicePrefrerences.end();
}

void setNetworkPreferences(const String &ssid, const String &password)
{
    devicePrefrerences.begin("devicePrefs", false);

    devicePrefrerences.putString("wifi_ssid", ssid);
    devicePrefrerences.putString("wifi_password", password);

    wifi_ssid = ssid;
    wifi_password = password;

    devicePrefrerences.end();
}

void eraseNVS()
{
    esp_err_t err = nvs_flash_erase();
    if (err == ESP_OK)
    {
        ESP.restart();
        return;
    }

    Serial.printf("Error erasing NVS flash: %d\n", err);
}
