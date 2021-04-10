#include "network/webServer/LedClient.h"
LedClient::LedClient(String IPaddress)
{
    address = IPaddress;
    lastUpdate = millis();
}

void LedClient::update()
{
    lastUpdate = millis();
}
