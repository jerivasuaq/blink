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
#ifndef MQTT_BROKER
#define MQTT_BROKER "test.mosquitto.org"
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#ifndef MQTT_TOPIC
#define MQTT_TOPIC "blink/test"
#endif

#ifndef MQTT_CLIENT_ID
#define MQTT_CLIENT_ID "blinkClient"
#endif

// LED pin
#define LED_PIN 2

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

extern const char* ssid;
extern const char* password;

#endif // CONFIG_H
