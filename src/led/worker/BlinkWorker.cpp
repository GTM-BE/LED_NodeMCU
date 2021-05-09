#include <Arduino.h>
#include "led/worker/BlinkWorker.h"
#include "led/LedControl.h"
#include "main.h"

BlinkWorker::BlinkWorker(unsigned int _onDelay, unsigned int _offDelay, RGB *_color) : Worker(WorkerID::BLINK_WORKER)
{
  onDelay = _onDelay;
  offDelay = _offDelay;
  color = _color;
};
BlinkWorker::BlinkWorker(unsigned int delay, RGB *_color)
{
  onDelay = delay;
  offDelay = delay;
  color = _color;
};

void BlinkWorker::onTick()
{
  if (analogRead(LED_RED) > 0)
  {
    if ((millis() + offDelay) < millis())
      LedControl::setColor(color->red, color->green, color->blue);
  }
  else
  {
    if ((millis() + onDelay) < millis())
      LedControl::setColor(LOW, LOW, LOW);
  }
};
