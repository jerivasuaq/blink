#include <Arduino.h>
#include "WiFiManager.h"
#include "Logger.h"

// WiFi credentials from .env file
#ifndef WIFI_SSID
#define WIFI_SSID "YOUR_SSID"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "YOUR_PASSWORD"
#endif

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// LED pin
const int LED = 2;

// WiFiManager instance
WiFiManager wifiManager(ssid, password);

void setup(){
    Serial.begin(115200);
    delay(1000); // Wait for Serial to initialize
    
    // Configure logger
    logger.setLogLevel(LOG_DEBUG);
    logger.setTimestamp(true);
    logger.setColors(true);
    
    logger.info("Main", "Starting blink application with WiFi support");
    
    pinMode(LED, OUTPUT);
    
    // Connect to WiFi
    if (wifiManager.connect()) {
        logger.info("Main", "WiFi connection successful!");
    } else {
        logger.warn("Main", "WiFi connection failed, continuing with LED blink");
    }
}

void loop(){
    // Blink LED
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
    
    // Print WiFi status periodically
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 10000) { // Every 10 seconds
        lastPrint = millis();
        if (wifiManager.isConnected()) {
            logger.debugf("Main", "WiFi Status: %s, Signal: %d dBm", 
                         wifiManager.getStatusString().c_str(),
                         wifiManager.getSignalStrength());
        } else {
            logger.warn("Main", "WiFi disconnected");
        }
    }
}
