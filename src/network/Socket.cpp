
#include <Arduino.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include "config.h"
#include "Socket.h"

void Socket::tick()
{
  Serial.println("Tick not defined");
}

void Socket::bind()
{
  connection.begin(WIFI_PORT);
  while (WiFi.status() == WL_CONNECTED)
  {
    tick();
    delay(0.001);
  }
  Serial.println("Connection lost!");
};
