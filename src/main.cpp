#include "Config.h"
#include <Arduino.h>
#include "WiFiManager.h"
#include "Logger.h"
#include "MQTTManager.h"

// WiFiManager instance
WiFiManager wifiManager(ssid, password);

// MQTTManager instance
MQTTManager mqttManager(MQTT_BROKER, MQTT_PORT);

// MQTT message callback
void mqttCallback(char* topic, uint8_t* payload, unsigned int length) {
    logger.infof("MQTT", "📩 Message received on topic: %s", topic);
    String msg;
    for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
    logger.infof("MQTT", "🔔 Payload: %s", msg.c_str());
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    logger.setLogLevel(LOG_DEBUG);
    logger.setTimestamp(true);
    logger.setColors(true);
    logger.info("Main", "Starting blink application with WiFi & MQTT support");
    logger.info("SSID", ssid);
    pinMode(LED_PIN, OUTPUT);
    if (wifiManager.connect()) {
        logger.info("Main", "WiFi connection successful!");
    } else {
        logger.warn("Main", "WiFi connection failed, continuing with LED blink");
    }
    mqttManager.setCallback(mqttCallback);
    if (mqttManager.connect(MQTT_CLIENT_ID)) {
        logger.info("MQTT", "✅ Connected to MQTT broker!");
        mqttManager.subscribe(MQTT_TOPIC);
        logger.infof("MQTT", "🔔 Subscribed to topic: %s", MQTT_TOPIC);
        mqttManager.publish(MQTT_TOPIC, "Hello from ESP32!");
        logger.info("MQTT", "📤 Published initial message");
    } else {
        logger.error("MQTT", "❌ MQTT connection failed");
    }
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 10000) {
        lastPrint = millis();
        if (wifiManager.isConnected()) {
            logger.debugf("Main", "WiFi Status: %s, Signal: %d dBm", wifiManager.getStatusString().c_str(), wifiManager.getSignalStrength());
        } else {
            logger.warn("Main", "WiFi disconnected");
        }
    }
    mqttManager.loop();
}
