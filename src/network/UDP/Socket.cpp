
#include <iostream>
#include <Arduino.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include "config.h"
#include "network/UDP/Socket.h"
#include "network/UDP/Packet.h"

#include "network/UDP/packets/SetColorPacket.h"

void Socket::tick()
{
  Serial.println("Tick not defined");
}

void Socket::bind()
{
#if SYSTEM == 0
  connection.begin(rand() % 6000 + 7000);
#else
  connection.begin(CLIENT_PORT);
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
    return std::unique_ptr<Packet>(new SetColorPacket(buffer));
    break;
  default:
    return std::unique_ptr<Packet>(new Packet(buffer));
    break;
  }
}

std::unique_ptr<Packet> Socket::PacketFromID(PacketID id)
{
  switch (id)
  {
  case PacketID::RGB_PACKET:
    return std::unique_ptr<Packet>(new SetColorPacket());
    break;
  default:
    return std::unique_ptr<Packet>(new Packet(PacketID::INVALID_PACKET));
    break;
  }
}
