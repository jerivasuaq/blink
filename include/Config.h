#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials from .env file
#ifndef WIFI_SSID
#define WIFI_SSID "YOUR_SSID"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "YOUR_PASSWORD"
#endif

// MQTT broker settings
#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT 1883
#define MQTT_TOPIC "blink/test"
#define MQTT_CLIENT_ID "blinkClient"

// LED pin
#define LED_PIN 2

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

extern const char* ssid;
extern const char* password;

#endif // CONFIG_H
