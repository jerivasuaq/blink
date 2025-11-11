#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

class WiFiManager {
private:
    const char* ssid;
    const char* password;
    int maxAttempts;
    int delayMs;
    
public:
    // Constructor
    WiFiManager(const char* ssid, const char* password, int maxAttempts = 20, int delayMs = 500);
    
    // Connect to WiFi network
    bool connect();
    
    // Disconnect from WiFi network
    void disconnect();
    
    // Check if connected to WiFi
    bool isConnected();
    
    // Get local IP address
    IPAddress getLocalIP();
    
    // Get signal strength in dBm
    int32_t getSignalStrength();
    
    // Get connection status as string
    String getStatusString();
};

#endif // WIFI_MANAGER_H
