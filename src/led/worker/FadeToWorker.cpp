#include <Arduino.h>
#include "led/worker/FadeToWorker.h"
#include "led/LedControl.h"
#include "led/Worker.h"
#include "config.h"
#include "led/RGB.h"

FadeToWorker::FadeToWorker(RGB *color) : Worker(WorkerID::FADE_TO_WORKER)
{
  this->fadeColor = color;
}

FadeToWorker::FadeToWorker(RGB *color, unsigned int step) : Worker(WorkerID::FADE_TO_WORKER)
{
  this->fadeColor = color;
  this->fadeStep = step;
}

void FadeToWorker::onPrepare()
{
  this->initColor = LedControl::getColor();
}

void FadeToWorker::onTick()
{
  this->currentColor->red = fadeChannel(LED_RED, fadeColor->red, currentColor->red, initColor->red);
  this->currentColor->green = fadeChannel(LED_GREEN, fadeColor->green, currentColor->green, initColor->green);
  this->currentColor->blue = fadeChannel(LED_BLUE, fadeColor->blue, currentColor->blue, initColor->blue);

  if (this->currentColor->red == this->fadeColor->red &&
      this->currentColor->green == this->fadeColor->green &&
      this->currentColor->blue == this->fadeColor->blue)
    this->status = WorkerStatus::FINISHED_WORKER;
}

unsigned int FadeToWorker::fadeChannel(uint8_t channel,
                                       unsigned int targetColor,
                                       unsigned int currentColor,
                                       unsigned int initColor)
{
  if (std::abs((int)targetColor - (int)currentColor) < this->fadeStep)
  {
    analogWrite(channel, targetColor);
    return targetColor;
  }
  int step = currentColor < targetColor ? this->fadeStep : this->fadeStep * -1;
  unsigned int newVal = currentColor + step;
  analogWrite(channel, newVal);
  return newVal;
}
