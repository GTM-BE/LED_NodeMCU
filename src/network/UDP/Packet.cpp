#include <Arduino.h>
#include <WiFiUdp.h>
#include "network/UDP/Packet.h"

Packet::Packet(PacketID packetID)
{
  id = packetID;
}

Packet::Packet(char *buf)
{
  for (size_t i = 0; i < sizeof(buffer) / sizeof(buffer[0]); i++)
  {
    buffer[i] = buf[i];
  }
}

void Packet::encode()
{
  Serial.println("Encode function not implemented");
}

void Packet::decode()
{
  Serial.println("Decode function not implemented");
}

void Packet::handle()
{
  Serial.println("Handle function not implemented");
}

void Packet::resetOffset()
{
  offset = 1;
}

void Packet::writeInt(unsigned int value)
{
  buffer[offset] = (value & 0xFF); //extract first byte
  offset++;
  buffer[offset] = ((value >> 8) & 0xFF); //extract second byte
  offset++;
  buffer[offset] = ((value >> 16) & 0xFF); //extract third byte
  offset++;
  buffer[offset] = ((value >> 24) & 0xFF); //extract fourth byte
  offset++;
}

unsigned int Packet::readInt()
{
  char byte1 = buffer[offset];
  offset++;
  char byte2 = buffer[offset];
  offset++;
  char byte3 = buffer[offset];
  offset++;
  char byte4 = buffer[offset];
  offset++;
  return (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
}

void Packet::writeLong(unsigned long value)
{
  unsigned int int1 = (value & 0xFFFFFFFF);
  unsigned int int2 = ((value >> 24) & 0xFFFFFFFF);
  writeInt(int1);
  writeInt(int2);
}

unsigned long Packet::readLong()
{
  unsigned int int1 = readInt();
  unsigned int int2 = readInt();
  return ((int2 << 24) | int1);
}

void Packet::writeString(String value)
{
  writeInt(value.length());
  offset++;
  for (unsigned int i = 0; i < value.length(); i++)
  {
    buffer[offset] = value.charAt(i);
    offset++;
  }
}

String Packet::readString()
{
  unsigned int stringSize = readInt();
  String stringBuf;
  for (unsigned int i = 0; i < stringSize; i++)
  {
    stringBuf += buffer[offset];
    offset++;
  }
  return stringBuf;
}

void Packet::writeBool(bool value)
{
  buffer[offset] = value;
  offset++;
}

bool Packet::readBool()
{
  bool value = &buffer[offset];
  offset++;
  return value;
}

void Packet::setOffset(unsigned int value)
{
  offset = value;
}
unsigned int Packet::getOffset()
{
  return offset;
};

void Packet::setPayload()
{
  resetOffset();
  buffer[0] = id;
  writeLong(number);
}

void Packet::getPayload()
{
  resetOffset();
  id = (PacketID)buffer[0];
  number = readLong();
}

char *Packet::getBuffer()
{
  return buffer;
}

bool Packet::send(WiFiUDP connection)
{
  connection.write(buffer);
  return true;
}
