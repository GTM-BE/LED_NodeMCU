
#include <Arduino.h>
#include "PacketRGB.h"
#include "Packet.h"

PacketRGB::PacketRGB(char *incommingBuffer) : Packet(incommingBuffer) {}
PacketRGB::PacketRGB() : Packet() {}

void PacketRGB::encode()
{
  writePacketID(PacketID::RGB_PACKET);
  resetOffset();
  writeInt(red);
  writeInt(green);
  writeInt(blue);
}

void PacketRGB::decode()
{
  resetOffset();
  red = readInt();
  green = readInt();
  blue = readInt();
}

void PacketRGB::handle()
{
  analogWrite(LED_RED, red);
  analogWrite(LED_GREEN, green);
  analogWrite(LED_BLUE, blue);
}
