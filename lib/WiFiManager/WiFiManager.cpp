#include "WiFiManager.h"
#include "../Logger/Logger.h"

WiFiManager::WiFiManager(const char* ssid, const char* password, int maxAttempts, int delayMs)
    : ssid(ssid), password(password), maxAttempts(maxAttempts), delayMs(delayMs) {
}

bool WiFiManager::connect() {
    logger.info("WiFiManager", "🚀 Starting WiFi connection...");
    logger.infof("WiFiManager", "🔗 Connecting to SSID: %s", ssid);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
        delay(delayMs);
        logger.debugf("WiFiManager", "🔄 Attempt %d/%d...", attempts + 1, maxAttempts);
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        logger.info("WiFiManager", "✅ WiFi connected!");
        logger.infof("WiFiManager", "🌐 IP address: %s", WiFi.localIP().toString().c_str());
        logger.infof("WiFiManager", "📶 SSID: %s", WiFi.SSID().c_str());
        logger.infof("WiFiManager", "📡 Signal strength: %d dBm", WiFi.RSSI());
        return true;
    } else {
        logger.error("WiFiManager", "❌ Failed to connect to WiFi");
        return false;
    }
}

void WiFiManager::disconnect() {
    logger.info("WiFiManager", "🔌 Disconnecting from WiFi...");
    WiFi.disconnect(true); // true = turn off WiFi radio
    logger.info("WiFiManager", "📴 WiFi disconnected");
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

IPAddress WiFiManager::getLocalIP() {
    return WiFi.localIP();
}

int32_t WiFiManager::getSignalStrength() {
    return WiFi.RSSI();
}

String WiFiManager::getStatusString() {
    switch (WiFi.status()) {
        case WL_CONNECTED:
            return "Connected";
        case WL_NO_SSID_AVAIL:
            return "SSID not found";
        case WL_CONNECT_FAILED:
            return "Connection failed";
        case WL_IDLE_STATUS:
            return "Idle";
        case WL_DISCONNECTED:
            return "Disconnected";
        default:
            return "Unknown";
    }
}
