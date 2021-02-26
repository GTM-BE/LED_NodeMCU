#include "Packet.h"

void Packet::writeInt(int value)
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

int Packet::readInt()
{
  char bit1 = buffer[offset];
  offset++;
  char bit2 = buffer[offset];
  offset++;
  char bit3 = buffer[offset];
  offset++;
  char bit4 = buffer[offset];
  offset++;
  return (bit1 >> 24) + (bit2 >> 16) + (bit3 >> 8) + bit4;
}

void Packet::writeString(char value[])
{
  buffer[offset] = sizeof value;
  offset++;
  for (unsigned int i = 0; i < sizeof value; i++)
  {
    buffer[offset] = value[i];
    offset++;
  }
}

char *Packet::readString()
{
  char stringSize = buffer[offset];
  char stringBuffer[stringSize];
  offset++;
  for (int i = 0; i < stringSize; i++)
  {
    stringBuffer[i] = buffer[offset];
    offset++;
  }
  return stringBuffer;
}

void Packet::writeBool(bool value)
{
  buffer[offset] = value;
  offset++;
}

bool Packet::readBool()
{
  bool value = buffer[offset];
  offset++;
  return value;
}

void Packet::setOffset(int value)
{
  offset = value;
}

bool Packet::send()
{
  return true;
}
