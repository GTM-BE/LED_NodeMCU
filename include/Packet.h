#ifndef PACKET_H_
#define PACKET_H_

#include "config.h"

enum PacketID
{
  INVALID = 0x00,
  RGB_PACKET = 0x01
};

class Packet
{
public:
  unsigned int offset = 1;
  char buffer[256];

public:
  Packet();
  Packet(char *incommingBuffer);
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
  void setOffset(unsigned int value);
  void writePacketID(PacketID id);
  void resetOffset();
  bool send();
};

#endif
