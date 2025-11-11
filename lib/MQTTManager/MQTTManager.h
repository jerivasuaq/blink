#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTManager {
private:
    WiFiClient wifiClient;
    PubSubClient mqttClient;
    const char* broker;
    uint16_t port;
    const char* user;
    const char* pass;
    void (*messageCallback)(char*, uint8_t*, unsigned int);

public:
    MQTTManager(const char* broker, uint16_t port = 1883, const char* user = nullptr, const char* pass = nullptr);
    void setCallback(void (*callback)(char*, uint8_t*, unsigned int));
    bool connect(const char* clientId);
    void loop();
    bool publish(const char* topic, const char* payload);
    bool subscribe(const char* topic);
    bool isConnected();
};

#endif // MQTT_MANAGER_H
