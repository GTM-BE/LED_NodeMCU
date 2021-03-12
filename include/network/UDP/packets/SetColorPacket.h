#ifndef PACKET_RGB_H_
#define PACKET_RGB_H_

#include "network/UDP/Packet.h"

class SetColorPacket : public Packet
{
public:
  unsigned int red = 0;
  unsigned int green = 0;
  unsigned int blue = 0;

public:
  SetColorPacket();
  SetColorPacket(char *buf);
  void encode() override;
  void decode() override;
  void handle() override;
};

#endif
