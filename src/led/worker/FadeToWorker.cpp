#include <Arduino.h>
#include "led/worker/FadeToWorker.h"
#include "led/LedControl.h"
#include "led/Worker.h"
#include "config.h"

FadeToWorker::FadeToWorker(RGB *color) : Worker(WorkerID::FADE_TO_WORKER)
{
  fadeColor = color;
}

FadeToWorker::FadeToWorker(RGB *color, unsigned int step) : Worker(WorkerID::FADE_TO_WORKER)
{
  fadeColor = color;
  fadeStep = step;
}

void FadeToWorker::onTick()
{
  fadeChannel(LED_RED, fadeColor->red);
  fadeChannel(LED_GREEN, fadeColor->green);
  fadeChannel(LED_BLUE, fadeColor->blue);
}

void FadeToWorker::fadeChannel(uint8_t channel, signed int targetBrightness)
{
  int brightness;
  if (analogRead(channel) < targetBrightness)
  {
    brightness = analogRead(channel) + fadeStep;
    if (brightness > targetBrightness)
    {
      brightness = 1024;
    }
    analogWrite(channel, brightness);
  }
  else
  {
    brightness = analogRead(channel) - fadeStep;
    if (brightness < targetBrightness)
    {
      brightness = 0;
    }
    analogWrite(channel, brightness);
  }
}
