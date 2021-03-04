#include <Arduino.h>
#include <WiFiUdp.h>
#include "Packet.h"

Packet::Packet()
{
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
  /*
  Serial.print("Buffer: ");
  for (size_t i = 0; i < sizeof(buffer) / sizeof(buffer[0]); i++)
  {
    Serial.printf("%c ", buffer[i]);
  }
  Serial.print("\n");
  Serial.printf("Offset %d\n", offset);
  */
  char byte1 = (value & 0xFF); //extract first byte
  buffer[offset] = byte1;
  offset++;
  char byte2 = ((value >> 8) & 0xFF); //extract second byte
  buffer[offset] = byte2;
  offset++;
  char byte3 = ((value >> 16) & 0xFF); //extract third byte
  buffer[offset] = byte3;
  offset++;
  char byte4 = ((value >> 24) & 0xFF); //extract fourth byte
  buffer[offset] = byte4;
  offset++;
  // Serial.printf("Bit1: %d Bit2: %d Bit3: %d Bit4: %d\n", byte1, byte2, byte3, byte4);
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
  // Serial.printf("Bit1: %d Bit2: %d Bit3: %d Bit4: %d\n", byte1, byte2, byte3, byte4);
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

void Packet::writePacketID(PacketID id)
{
  buffer[0] = id;
}

void Packet::setOffset(unsigned int value)
{
  offset = value;
}
unsigned int Packet::getOffset()
{
  return offset;
};

char *Packet::getBuffer()
{
  return buffer;
}
bool Packet::send(WiFiUDP connection)
{
  connection.write(buffer);
  return true;
}
