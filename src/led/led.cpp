#include <Arduino.h>
#include "config.h"

int emit = 0;
int step = 1;

void flipLED()
{
  digitalWrite(LED_BLUE, !digitalRead(LED_BLUE));
  Serial.write("Signale Changed! \r\n");
}

void fadeLED()
{
  if (emit <= 1)
  {
    step = 1;
  }
  else if (emit >= 1024)
  {
    step = -1;
  }

  analogWrite(LED_RED, emit);
  analogWrite(LED_GREEN, emit);
  analogWrite(LED_BLUE, emit);
  emit = emit + step;
  delay(10);
  //Serial.printf("%d\r\n", emit);
}
