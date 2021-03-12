
#include <Arduino.h>
#include "config.h"
#include "network/UDP/UdpClient.h"
#include "network/UDP/packets/SetColorPacket.h"

void UdpClient::tick()
{
  int packetSize = connection.parsePacket();
  if (packetSize)
  {

    // receive incoming UDP packets
    // Serial.printf("Received %d bytes from %s, port %d\n", packetSize, connection.remoteIP().toString().c_str(), connection.remotePort());

    int length = connection.read(packetBuffer, MAX_PACKET_LENGTH);
    if (length > 0)
    {
      packetBuffer[length] = 0;
    }

    std::unique_ptr<Packet> pk = PacketFromBuffer(packetBuffer);

    pk->decode();
    pk->handle();
  }

  ledController.tick();
}
