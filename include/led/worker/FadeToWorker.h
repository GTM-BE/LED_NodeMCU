#ifndef FADE_TO_WORKER_H_
#define FADE_TO_WORKER_H_

#include "led/Worker.h"
#include "led/LedControl.h"

class FadeToWorker : public Worker
{
public:
  RGB fadeColor;
  unsigned int fadeStep;

public:
  FadeToWorker(RGB color);
  FadeToWorker(RGB color, unsigned int step);
  void onTick() override;
  void fadeChannel(uint8_t channel, signed int brightness);
};

#endif
