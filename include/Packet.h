#ifndef PACKET_H_
#define PACKET_H_

#include <WiFiUdp.h>
#include "config.h"

enum PacketID
{
  INVALID = 0x00,
  TEST_PACKET = 0x01,
  RGB_PACKET = 0x02
};

class Packet
{
public:
  unsigned int offset = 0;

public:
  char buffer[255];

public:
  Packet();
  Packet(char *buf);
  virtual void encode();
  virtual void decode();
  virtual void handle();

  void writeInt(unsigned int value);
  unsigned int readInt();
  void writeLong(unsigned long value);
  unsigned long readLong();
  void writeString(String value);
  String readString();
  void writeBool(bool value);
  bool readBool();
  void writePacketID(PacketID id);
  void setOffset(unsigned int value);
  unsigned int getOffset();
  char *getBuffer();
  void resetOffset();
  bool send(WiFiUDP connection);
};

#endif
