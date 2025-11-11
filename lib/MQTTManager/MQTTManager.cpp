#include "MQTTManager.h"

MQTTManager::MQTTManager(const char* broker, uint16_t port, const char* user, const char* pass)
    : broker(broker), port(port), user(user), pass(pass), mqttClient(wifiClient), messageCallback(nullptr) {
    mqttClient.setServer(broker, port);
}

void MQTTManager::setCallback(void (*callback)(char*, uint8_t*, unsigned int)) {
    messageCallback = callback;
    mqttClient.setCallback(callback);
}

bool MQTTManager::connect(const char* clientId) {
    if (user && pass) {
        return mqttClient.connect(clientId, user, pass);
    } else {
        return mqttClient.connect(clientId);
    }
}

void MQTTManager::loop() {
    mqttClient.loop();
}

bool MQTTManager::publish(const char* topic, const char* payload) {
    return mqttClient.publish(topic, payload);
}

bool MQTTManager::subscribe(const char* topic) {
    return mqttClient.subscribe(topic);
}

bool MQTTManager::isConnected() {
    return mqttClient.connected();
}
