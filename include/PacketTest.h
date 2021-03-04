#ifndef PACKET_TEST_H_
#define PACKET_TEST_H_

#include "Packet.h"

class PacketTest : public Packet
{
public:
  String customString;
  unsigned int unsInt = 0;
  unsigned long unsLong = 0;

public:
  PacketTest();
  PacketTest(char *buf);
  void encode() override;
  void decode() override;
  void handle() override;
};

#endif
