#ifndef BLINK_WORKER_H_
#define BLINK_WORKER_H_

#include "led/Worker.h"
#include "led/LedControl.h"

class BlinkWorker : public Worker
{
public:
  unsigned int onDelay = 1000;
  unsigned int offDelay = 1000;
  RGB *color;

public:
  BlinkWorker(unsigned int _onDelay, unsigned int _offDelay, RGB *_color);
  BlinkWorker(unsigned int delay, RGB *_color);
  void onTick() override;
};

#endif
