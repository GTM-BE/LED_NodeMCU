
#include <Arduino.h>
#include "config.h"
#include "UdpClient.h"
#include "PacketRGB.h"

void UdpClient::tick()
{
  int packetSize = connection.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, connection.remoteIP().toString().c_str(), connection.remotePort());
    int length = connection.read(packetBuffer, MAX_PACKET_LENGTH);
    if (length > 0)
    {
      packetBuffer[length] = 0;
    }

    PacketRGB *pk = new PacketRGB(packetBuffer);
    //std::unique_ptr<Packet> pk = PacketFromBuffer(packetBuffer);

    pk->decode();
    pk->handle();
    delete pk;
  }
}
