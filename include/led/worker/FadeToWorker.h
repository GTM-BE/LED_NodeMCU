#ifndef FADE_TO_WORKER_H_
#define FADE_TO_WORKER_H_

#include "led/Worker.h"
#include "led/LedControl.h"
#include "led/RGB.h"

class FadeToWorker : public Worker
{
public:
  RGB *fadeColor;
  RGB *initColor;
  unsigned int fadeStep = 1;

public:
  FadeToWorker(RGB *color);
  FadeToWorker(RGB *color, unsigned int step);
  void onTick() override;
  void onPrepare() override;
  unsigned int fadeChannel(uint8_t channel,
                           unsigned int targetColor,
                           unsigned int currentColor,
                           unsigned int initColor);
};

#endif
