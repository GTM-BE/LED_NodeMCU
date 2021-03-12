#ifndef SOCKET_H_
#define SOCKET_H_

#include <iostream>
#include <WiFiUdp.h>
#include "config.h"
#include "network/UDP/Packet.h"

class Socket
{
public:
  char packetBuffer[MAX_PACKET_LENGTH];
  WiFiUDP connection;

public:
  virtual void tick();
  void bind();
  std::unique_ptr<Packet> PacketFromBuffer(char *buffer);
  std::unique_ptr<Packet> PacketFromID(PacketID id);
};

#endif
