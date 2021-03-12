#include <Arduino.h>
#include "led/worker/BlinkWorker.h"
#include "led/LedControl.h"
#include "Config.h"

BlinkWorker::BlinkWorker(unsigned int _onDelay, unsigned int _offDelay) : Worker(WorkerID::BLINK_WORKER)
{
  onDelay = _onDelay;
  offDelay = _offDelay;
};

void BlinkWorker::onTick()
{
  if (analogRead(LED_RED) > 0)
  {
    if ((millis() + offDelay) < millis())
      LedControl::setColor(HIGH, HIGH, HIGH);
  }
  else
  {
    if ((millis() + onDelay) < millis())
      LedControl::setColor(LOW, LOW, LOW);
  }
};
