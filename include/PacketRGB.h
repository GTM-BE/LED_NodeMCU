#ifndef PACKET_RGB_H_
#define PACKET_RGB_H_

#include "Packet.h"

class PacketRGB : public Packet
{
private:
  int red = 0;
  int green = 0;
  int blue = 0;

public:
  void encode(char *buffer) override;
  void decode(char *buffer) override;
  void handle() override;
};

#endif
