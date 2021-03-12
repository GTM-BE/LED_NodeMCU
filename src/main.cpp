#include <Arduino.h>
#include "network/Connection.h"
#include "config.h"

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  Serial.write("\r\n");
  connect();
}

void loop()
{
}
