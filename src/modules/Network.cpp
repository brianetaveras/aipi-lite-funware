
#include <WiFi.h>
#include <WebServer.h>
#include "Network.h"
#include "Filesystem.h"

#include <modules/Display.h>
#include "DevicePreferences.h"

WebServer server(80);
Network net;

static const char *kIndexPath = "/index.html";
static const char *kIndexPathGz = "/index.html.gz"; // optional gzip
static const char *kCssPath = "/nes.min.css";
static const char *kCssPathGz = "/nes.min.css.gz"; // optional gzip
static const char *kFontPath = "/fonts/PressStart2P.woff2";

String AccessPointSSID = "BSoft_Setup";
String AccessPointPassword = "";

Network::Network() {}

bool Network::isNetworkConfigured() const
{
    return wifi_ssid.length() > 0;
}

static void sendStaticFile(const char *plainPath, const char *gzPath,
                           const char *mimeType, const char *cacheCtl = "max-age=31536000")
{
    // Prefer gzip if present
    File f;
    Serial.printf("[DEBUG] sendStaticFile: gzPath=%s plainPath=%s\n", gzPath ? gzPath : "(null)", plainPath ? plainPath : "(null)");
    if (gzPath && fileExists(gzPath))
    {
        f = openFile(gzPath, "r");
        if (!f || !f.available())
        {
            Serial.printf("[ERROR] Failed to open gzipped file: %s\n", gzPath);
            server.send(500, "text/plain", "FS open error (gz)");
            return;
        }
        server.sendHeader("Cache-Control", cacheCtl);
        server.sendHeader("Content-Encoding", "gzip");
        server.streamFile(f, mimeType);
        f.close();
        return;
    }
    // Fallback to plain
    if (plainPath && fileExists(plainPath))
    {
        f = openFile(plainPath, "r");
        if (!f || !f.available())
        {
            Serial.printf("[ERROR] Failed to open plain file: %s\n", plainPath);
            server.send(404, "text/plain", "Not found (plain)");
            return;
        }
        server.sendHeader("Cache-Control", cacheCtl);
        server.streamFile(f, mimeType);
        f.close();
    }
    else
    {
        Serial.printf("[ERROR] File not found: %s\n", plainPath ? plainPath : "(null)");
        server.send(404, "text/plain", "Not found");
    }
}

// Build <option> list safely (escape HTML entities for SSIDs)
static String htmlEscape(const String &s)
{
    String out;
    out.reserve(s.length() + 8);
    for (size_t i = 0; i < s.length(); ++i)
    {
        char c = s[i];
        switch (c)
        {
        case '&':
            out += F("&amp;");
            break;
        case '<':
            out += F("&lt;");
            break;
        case '>':
            out += F("&gt;");
            break;
        case '"':
            out += F("&quot;");
            break;
        case '\'':
            out += F("&#39;");
            break;
        default:
            out += c;
            break;
        }
    }
    return out;
}

static String buildSsidOptions()
{
    int n = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);
    String opts;
    opts.reserve(64 * (n > 0 ? n : 1));
    if (n <= 0)
    {
        opts += F("<option value=\"\">(no networks found)</option>");
        return opts;
    }
    for (int i = 0; i < n; ++i)
    {
        String ssid = htmlEscape(WiFi.SSID(i));
        if (ssid.length() == 0)
            continue;
        opts += F("<option value=\"");
        opts += ssid;
        opts += F("\">");
        opts += ssid;
        opts += F("</option>");
    }
    return opts;
}

void Network::startAccessPoint()
{

    WiFi.mode(WIFI_AP);
    WiFi.softAP(AccessPointSSID.c_str(), AccessPointPassword.c_str());

    // HTML route: load template, inject SSIDs
    server.on("/", HTTP_GET, []
              {
        const char* path = fileExists(kIndexPath) ? kIndexPath : nullptr;
        const char* gz   = fileExists(kIndexPathGz) ? kIndexPathGz : nullptr;
        Serial.printf("[DEBUG] GET /: path=%s gz=%s\n", path ? path : "(null)", gz ? gz : "(null)");
        if (!path) {
            Serial.println("[ERROR] index.html not found in FS");
            server.send(404, "text/plain", "index.html not found");
            return;
        }
        File f = openFile(path, "r");
        if (!f || !f.available()) {
            Serial.printf("[ERROR] Failed to open index.html: %s\n", path);
            server.send(500, "text/plain", "index open failed");
            return;
        }
        String html; html.reserve(f.size() + 512);
        while (f.available()) html += (char)f.read();
        f.close();
        html.replace(F("%%SSID_OPTIONS%%"), buildSsidOptions());
        server.send(200, "text/html; charset=UTF-8", html); });

    // Static assets
    server.on("/nes.min.css", HTTP_GET, []
              { sendStaticFile(kCssPath, kCssPathGz, "text/css"); });
    server.on("/fonts/PressStart2P.woff2", HTTP_GET, []
              { sendStaticFile(kFontPath, nullptr, "font/woff2"); });

    // POST handler
    server.on("/", HTTP_POST, []
              {
                  String ssid = server.arg("ssid");
                  String password = server.arg("password");
                  net.handleFormSubmission(ssid.c_str(), password.c_str());
                  server.send(200, "text/plain", "Credentials saved. Rebooting...");
                  //   delay(1000);
                  //   ESP.restart();
              });

    server.begin();
}

void Network::handleFormSubmission(const std::string &ssid, const std::string &password)
{
    connectToWiFi(ssid.c_str(), password.c_str());
}

void Network::connectToWiFi(const char *ssid, const char *password)
{
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("BSoft_Device");
    WiFi.begin(ssid, password);

    lcd.fillScreen(ST7735_BLACK);
    lcd.setCursor(10, 50);
    lcd.println("Connecting...");

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        attempts++;
    }

    // Optionally, add code here to check connection status and update the display
    if (WiFi.status() == WL_CONNECTED)
    {
        lcd.fillScreen(ST7735_BLACK);

        lcd.setCursor(10, 30);
        lcd.println("Connected!");
        lcd.setCursor(10, 50);
        lcd.print("IP: ");
        lcd.println(WiFi.localIP().toString());

        setNetworkPreferences(String(ssid), String(password));
        return;
    }

    lcd.setCursor(10, 30);
    lcd.println("Connection Failed!");
    setNetworkPreferences(String(""), String(""));
}

std::vector<std::string> Network::scanAvailableNetworks() const
{
    std::vector<std::string> networks;
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i)
        networks.push_back(WiFi.SSID(i).c_str());
    return networks;
}

void setupNetwork()
{

    if (!net.isNetworkConfigured())
    {
        net.startAccessPoint();
        lcd.fillScreen(ST7735_BLACK);
        lcd.setCursor(10, 10);
        lcd.setTextColor(ST7735_WHITE);
        lcd.setTextSize(1);
        lcd.println("Network Config Mode");
        lcd.setCursor(10, 30);
        lcd.println("SSID: " + AccessPointSSID);
        lcd.setCursor(10, 50);
        lcd.println("Password: " + AccessPointPassword);
        lcd.setCursor(10, 70);
        lcd.println("Navigate to:");
        lcd.setCursor(10, 90);
        lcd.println("http://192.168.4.1");

        while (true)
        {
            server.handleClient();
            delay(10);
        }
        return;
    }

    lcd.fillScreen(ST7735_BLACK);
    lcd.setCursor(10, 10);
    lcd.setTextColor(ST7735_WHITE);
    lcd.setTextSize(1);
    lcd.println("Connecting to WiFi...");
    net.connectToWiFi(wifi_ssid.c_str(), wifi_password.c_str());
}


void networkLoop()
{
    if (net.isNetworkConfigured()){
        return;
    }
    server.handleClient();
    delay(10);
}