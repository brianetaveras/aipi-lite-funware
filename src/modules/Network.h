
#pragma once

#include <string>
#include <vector>

class Network
{
public:
    Network();
    bool isNetworkConfigured() const;
    void startAccessPoint();
    void serveConfigForm();
    void handleFormSubmission(const std::string &ssid, const std::string &password);
    void connectToWiFi(char const *ssid, char const *password);
    std::vector<std::string> scanAvailableNetworks() const;
};

void setupNetwork();

void networkLoop();