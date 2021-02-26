
#include <Arduino.h>
#include "UdpClient.h"

void UdpClient::tick()
{
  int packetSize = connection.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, connection.remoteIP().toString().c_str(), connection.remotePort());
    int length = connection.read(packetBuffer, 255);
    if (length > 0)
    {
      packetBuffer[length] = 0;
    }
    Serial.println(packetBuffer);
  }
}
