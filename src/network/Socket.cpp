
#include <Arduino.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include "config.h"
#include "Socket.h"
#include "Packet.h"

#include "PacketRGB.h"

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

Packet Socket::PacketFromBuffer(char *buffer)
{
  switch (buffer[0])
  {
  case PacketID::RGB_PACKET:
    Serial.println("Got RGB PK");
    PacketRGB rgb_pk(buffer);
    return rgb_pk;
    break;
  }
  Packet pk(buffer);
  return pk;
}
