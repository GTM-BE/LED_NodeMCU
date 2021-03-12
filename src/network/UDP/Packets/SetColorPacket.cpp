
#include <Arduino.h>
#include "network/UDP/packets/SetColorPacket.h"
#include "led/LedControl.h"
#include "network/UDP/Packet.h"

SetColorPacket::SetColorPacket() : Packet(PacketID::RGB_PACKET)
{
}

SetColorPacket::SetColorPacket(char *buf) : Packet(buf)
{
}

void SetColorPacket::encode()
{
  setPayload();
  writeInt(red);
  writeInt(green);
  writeInt(blue);
}

void SetColorPacket::decode()
{
  getPayload();
  red = readInt();
  green = readInt();
  blue = readInt();
}

void SetColorPacket::handle()
{
}
