#ifndef MAIN_H_
#define MAIN_H_
#include <IPAddress.h>
#include "led/LedControl.h"
#include <ESP8266HTTPClient.h>

extern IPAddress RasberriPI;
extern IPAddress subnet;
extern IPAddress gateway;
extern LedControl led;

extern WiFiClient wifiClient;
extern HTTPClient httpClient;

// general
#define testMode 1

// LED
#define LED_RED D1
#define LED_GREEN D2
#define LED_BLUE D3

// WIFI
#define WIFI_SSID "FRITZ!Box Fon WLAN 7360"
#define WIFI_PASSWORD "02199057144210921230"

// AP
#define AP_SSID "LED_WIFI_MCU"
#define AP_PASSWORD "1234567890"

// Serial console
#define enableSerial 0
#define BAUD_RATE 9200
#endif
