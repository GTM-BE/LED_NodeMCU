#ifndef CONFIG_H_
#define CONFIG_H_
#include <ESP8266WiFi.h>

// LED
#define LED_RED D1
#define LED_GREEN D2
#define LED_BLUE D3

// WIFI
#define WIFI_SSID "FRITZ!Box Fon WLAN 7360"
#define WIFI_PASSWORD "02199057144210921230"
#define WIFI_PORT 5555
#define IS_CLIENT true

// AP
#define AP_SSID "LED_WIFI_MCU"
#define AP_PASSWORD "1234567890"

// Serial console
#define BAUD_RATE 9200

#endif
