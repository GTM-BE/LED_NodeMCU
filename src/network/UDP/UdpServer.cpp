#include <Arduino.h>
#include "network/UDP/UdpServer.h"
#include "network/UDP/packets/SetColorPacket.h"
#include "config.h"
#include "network/Connection.h"

void UdpServer::tick()
{
  std::unique_ptr<SetColorPacket> pk = std::unique_ptr<SetColorPacket>(new SetColorPacket());
  pk->red = 0;
  pk->blue = 0;
  pk->green = 10;
  pk->encode();

  for (size_t i = 0; i < sizeof SlaveAddresses; i++)
  {
    connection.beginPacket(SlaveAddresses[i], CLIENT_PORT);
    connection.write(pk->getBuffer(), MAX_PACKET_LENGTH);
    connection.endPacket();
  }
}
