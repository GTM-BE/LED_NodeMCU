#ifndef PACKET_H
#define PACKET_H

#include "config.h"

enum PacketID
{
  INVALID = 0x00,
  COLOR_RGB_PACKET = 0x01
};

class Packet
{
public:
  int offset = 1;
  char buffer[256];
  virtual void encode(char *buffer);
  virtual void decode(char *buffer);
  virtual void handle();

  void writeInt(int value);
  int readInt();
  void writeString(char value[]);
  char *readString();
  void writeBool(bool value);
  bool readBool();
  void setOffset(int value);
  bool send();
};

#endif
