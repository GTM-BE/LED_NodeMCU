#include <Arduino.h>
#include "UdpServer.h"
#include "PacketRGB.h"
#include "config.h"
#include "Connection.h"
int _emit = 0;
int _step = 1;
void UdpServer::tick()
{
  if (_emit <= 1)
  {
    _step = 10;
  }
  else if (_emit >= 1024)
  {
    _step = -10;
  }
  _emit = _emit + _step;
  PacketRGB *pk = new PacketRGB();
  pk->red = 500;
  pk->blue = 500;
  Serial.printf("Value: %d", _emit);
  pk->green = _emit;
  pk->encode();

  for (size_t i = 0; i < sizeof SlaveAddresses; i++)
  {
    connection.beginPacket(SlaveAddresses[i], WIFI_PORT);
    connection.write(pk->getBuffer(), MAX_PACKET_LENGTH);
    connection.endPacket();
  }

  Serial.println("Packets send to salve devices");
  delete pk;
}
