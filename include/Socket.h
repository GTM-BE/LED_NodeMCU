#ifndef SOCKET_H_
#define SOCKET_H_

#include <WiFiUdp.h>
#include "config.h"

class Socket
{
public:
  char packetBuffer[PACKET_SIZE];
  WiFiUDP connection;

public:
  virtual void tick();
  void bind();
};

#endif
