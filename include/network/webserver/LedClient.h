#ifndef LED_CLIENT_H_
#define LED_CLIENT_H_
#include "AsyncJson.h"
#include "ArduinoJson.h"

class LedClient
{
public:
    String address = "0.0.0.0";
    int lastUpdate = 0;

public:
    LedClient(String IPaddress);
    void update();
};

#endif
