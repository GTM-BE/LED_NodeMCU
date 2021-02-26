
#include <Arduino.h>
#include "PacketRGB.h"

void PacketRGB::encode(char *buffer)
{
  writeInt(red);
  writeInt(green);
  writeInt(blue);
}

void PacketRGB::decode(char *buffer)
{
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
