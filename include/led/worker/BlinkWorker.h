#ifndef BLINK_WORKER_H_
#define BLINK_WORKER_H_

#include "led/Worker.h"

class BlinkWorker : public Worker
{
public:
  unsigned int onDelay = 1000;
  unsigned int offDelay = 1000;

public:
  BlinkWorker(unsigned int _onDelay, unsigned int _offDelay);
  void onTick() override;
};

#endif
