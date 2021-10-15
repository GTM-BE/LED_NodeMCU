#ifndef WORKER_H_
#define WORKER_H_

#include <map>
#include "RGB.h"

enum WorkerStatus
{
  READY_WORKER,
  RUNNING_WORKER,
  FINISHED_WORKER
};

enum WorkerID
{
  INVALID_WORKER = 0x00,
  BLINK_WORKER = 0x01,
  FADE_TO_WORKER = 0x02,
  SET_COLOR_WORKER = 0x03
};

class Worker
{
public:
  WorkerID id = WorkerID::INVALID_WORKER;
  WorkerStatus status = WorkerStatus::READY_WORKER;
  unsigned long lastTick = 0;
  RGB *currentColor = new RGB(0, 0, 0);

public:
  Worker();
  Worker(WorkerID workerID);
  void tick();
  virtual void onTick();
  void prepare(RGB *color);
  virtual void onPrepare();
};

#endif
