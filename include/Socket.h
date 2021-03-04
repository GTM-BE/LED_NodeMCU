#ifndef SOCKET_H_
#define SOCKET_H_

#include <iostream>
#include <WiFiUdp.h>
#include "config.h"
#include "Packet.h"

class Socket
{
public:
  char packetBuffer[MAX_PACKET_LENGTH];
  WiFiUDP connection;

public:
  virtual void tick();
  void bind();
  std::unique_ptr<Packet> PacketFromBuffer(char *buffer);
};

#endif
