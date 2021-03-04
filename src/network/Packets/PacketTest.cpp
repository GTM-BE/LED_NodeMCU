
#include <Arduino.h>
#include "PacketTest.h"
#include "Packet.h"

PacketTest::PacketTest() : Packet() {}
PacketTest::PacketTest(char *buf) : Packet(buf) {}

void PacketTest::encode()
{
  writePacketID(PacketID::TEST_PACKET);
  resetOffset();
  writeString(customString);
}

void PacketTest::decode()
{
  resetOffset();
  customString = readString();
}

void PacketTest::handle()
{
  Serial.print("Test packet string: ");
  Serial.print(customString);
  Serial.print("\n");
}
