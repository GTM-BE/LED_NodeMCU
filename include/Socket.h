#ifndef SOCKET_H_
#define SOCKET_H_

#include <WiFiUdp.h>
#include "config.h"
#include "Packet.h"

class Socket
{
public:
  char packetBuffer[256];
  WiFiUDP connection;

public:
  virtual void tick();
  void bind();
  Packet PacketFromBuffer(char *buffer);
};

#endif
