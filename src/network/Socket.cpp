
#include <iostream>
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
#if SYSTEM == 0
  connection.begin(rand() % 6000 + 7000);
#else
  connection.begin(WIFI_PORT);
#endif

  while (WiFi.status() == WL_CONNECTED)
  {
    tick();
    delay(1);
  }
  Serial.println("Connection lost!");
};

std::unique_ptr<Packet> Socket::PacketFromBuffer(char buffer[])
{
  switch (buffer[0])
  {
  case PacketID::RGB_PACKET:
    return std::unique_ptr<Packet>(new PacketRGB(buffer));
    break;
  default:
    return std::unique_ptr<Packet>(new Packet(buffer));
    break;
  }
}
