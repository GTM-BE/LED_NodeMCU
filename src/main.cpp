#include <Arduino.h>
#include "Connection.h"
#include "config.h"
#include "led.h"

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_BLUE, OUTPUT); //LED pin as output
  Serial.begin(BAUD_RATE);
  Serial.write("\r\n");
  connect();
}

void loop()
{
  /*    
  flipLED();
  delay(100);
  */
  fadeLED();
}
